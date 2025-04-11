// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatComponent.h"
#include "ExtractionProtocol/Weapons/Base_Weapon.h"
#include "ExtractionProtocol/PlayerScripts/BaseCharacter.h"
#include "ExtractionProtocol/AIScripts/BaseAi.h"
#include "ExtractionProtocol/Other/Base_PlayerController.h"
#include "ExtractionProtocol/UI/Base_CharacterHUD.h"

#include "Engine/SkeletalMeshSocket.h"
#include "Components/SphereComponent.h"
#include "Net/UnrealNetwork.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"
#include "Engine/DamageEvents.h"
#include "Perception/AISense_Damage.h"

UCombatComponent::UCombatComponent()
{
	PrimaryComponentTick.bCanEverTick = false;		
}

void UCombatComponent::BeginPlay()
{
	Super::BeginPlay();	
}

void UCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UCombatComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UCombatComponent, EquippedWeapon);
	DOREPLIFETIME(UCombatComponent, ThirdPersonWeapon); // Replicating this causes the extra weapon to be hidden
	DOREPLIFETIME(UCombatComponent, bOwnerCanSee); // Replicating this causes the extra weapon to be hidden

	DOREPLIFETIME(UCombatComponent, CurrentAmmo);
	DOREPLIFETIME(UCombatComponent, CurrentReserveAmmo);
	DOREPLIFETIME(UCombatComponent, OnAmmoUse);		
}

void UCombatComponent::StartFire()
{	
	 Server_Fire();

	//if (EquippedWeapon)
	//{
	//	// Loops until TimerHandle is Cleared 
	//	if (!Character->GetIsDead())
	//	{
	//		FireShot();
	//		GetWorld()->GetTimerManager().SetTimer(TimerHandle_HandleFire, this, &ThisClass::FireShot, EquippedWeapon->WeaponProperties.FireRate, true);
	//	}
	//}
}

void UCombatComponent::StopFire()
{	
	Server_StopFire();

	/*if (EquippedWeapon)
	{
		Character->SetIsShooting(false);
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle_HandleFire);
	}*/

	
}

void UCombatComponent::FireShot()
{	
	if (!Character->HasAuthority())
	{			
		LocalFire();
	}
	 Server_FireShot();	
}

void UCombatComponent::Reload()
{	
	Server_Reload();

	//if (EquippedWeapon && CurrentAmmo != EquippedWeapon->WeaponProperties.Ammo)
	//{
	//	Character->SetIsReloading(true);
	//	CurrentReserveAmmo += CurrentAmmo; // Refil Reserve ammo with leftover from clip
	//	CurrentAmmo = EquippedWeapon->WeaponProperties.Ammo;
	//	CurrentReserveAmmo -= CurrentAmmo;
	//	OnAmmoUse.Broadcast(CurrentAmmo, CurrentReserveAmmo); // Updates HUD
	//}
}

void UCombatComponent::ReloadFinished()
{
	Character->SetIsReloading(false);	
}

void UCombatComponent::Restock()
{
	if (EquippedWeapon)
	{
		CurrentAmmo = EquippedWeapon->WeaponProperties.Ammo;
		CurrentReserveAmmo = EquippedWeapon->WeaponProperties.ReserveAmmo;
		OnAmmoUse.Broadcast(CurrentAmmo, CurrentReserveAmmo); // Updates HUD
	}
}


void UCombatComponent::LocalFire()
{
	if (Character->GetIsReloading()) { return; }

	if (CurrentAmmo <= 0)
	{
		if (EquippedWeapon->DryFireSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, EquippedWeapon->DryFireSound, EquippedWeapon->GetActorLocation());
		}

		StopFire();
		return;
	}

	CurrentAmmo--;
	OnAmmoUse.Broadcast(CurrentAmmo, CurrentReserveAmmo);
	Character->SetIsShooting(true);

	FHitResult Hit;
	const float WeaponRange = 20000.f; // CHANGE TO 20000
	// Changed from EquippedWeapon to ThirdPersonWeapon
	FVector StartTrace = ThirdPersonWeapon->GetWeaponMesh()->GetSocketByName("MuzzleFlash")->GetSocketLocation(ThirdPersonWeapon->GetWeaponMesh());
	FVector EndTrace = StartTrace + Character->Camera->GetForwardVector() * WeaponRange;
	/*CameraTransform = Character->Camera->GetForwardVector();
	if (!Character->IsLocallyControlled())
	{
		EndTrace = StartTrace + CameraTransform * WeaponRange;
		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Magenta, FString::Printf(TEXT("%s->Camera->GetForwardVector() = %s"), *Character->GetName(), *Character->Camera->GetForwardVector().ToString()));
	}*/
		
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(Character);
	QueryParams.AddIgnoredActor(EquippedWeapon);
	QueryParams.AddIgnoredActor(ThirdPersonWeapon);
	
	if (GetWorld()->LineTraceSingleByChannel(Hit, StartTrace, EndTrace, ECC_Visibility, QueryParams, FCollisionResponseParams()))
	{
		// AI Damage Sense info
		FPointDamageEvent DamageEvent;
		DamageEvent.Damage = EquippedWeapon->WeaponProperties.Damage;
		DamageEvent.ShotDirection = Character->GetActorLocation();
		UAISense_Damage::ReportDamageEvent(GetWorld(), Hit.GetActor(), Hit.GetActor()->GetInstigator(), DamageEvent.Damage, Character->GetActorLocation(), Hit.GetActor()->GetActorLocation());

		// Damage
		Hit.GetActor()->TakeDamage(EquippedWeapon->WeaponProperties.Damage, DamageEvent, Hit.GetActor()->GetInstigatorController(), Hit.GetActor()->GetInstigator());		

		// Add If AI is hit, Squish sound // Hayden- Use the ABaseAi header file trust will make things easier
		if (EquippedWeapon->BodyImpactSound && !Cast<UStaticMeshComponent>(Hit.GetComponent()))
		{
			UGameplayStatics::PlaySoundAtLocation(this, EquippedWeapon->BodyImpactSound, EquippedWeapon->GetActorLocation());
		}
		else if (EquippedWeapon->MissedImpactSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, EquippedWeapon->MissedImpactSound, Hit.GetActor()->GetActorLocation());
		}

		// Logs to check hit actor and hit actor component
		// GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Blue, FString::Printf(TEXT("Target hit: %s"), *Hit.GetActor()->GetName()));
		// GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Blue, FString::Printf(TEXT("Hit Component: %s"), *Hit.GetComponent()->GetName()));
	}

	// Draws Line Trace
	//DrawDebugLine(GetWorld(), StartTrace, EndTrace, FColor::Red, false, 5.f);
	//DrawDebugSphere(GetWorld(), EndTrace, 15.f, 1, FColor::Red, false, 10.f);

	if (EquippedWeapon->FireSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, EquippedWeapon->FireSound, EquippedWeapon->GetActorLocation());
	}

	if (EquippedWeapon->MuzzleParticles)
	{
		if (Character->IsLocallyControlled())
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), EquippedWeapon->MuzzleParticles, EquippedWeapon->GetWeaponMesh()->GetSocketTransform(FName("MuzzleFlash")));
			//GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Blue, FString::Printf(TEXT("LocallyControlled")));
		}

		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), EquippedWeapon->MuzzleParticles, ThirdPersonWeapon->GetWeaponMesh()->GetSocketTransform(FName("MuzzleFlash")));
	}
}

void UCombatComponent::EquipWeapon(ABase_Weapon* WeaponToEquip)
{
	if (Character == nullptr || WeaponToEquip == nullptr) return;

	EquippedWeapon = WeaponToEquip;
	EquippedWeapon->WeaponMesh->CastShadow = false;
	EquippedWeapon->SetWeaponState(EWeaponState::EWS_Equipped);
	CurrentAmmo = EquippedWeapon->WeaponProperties.Ammo;
	CurrentReserveAmmo = EquippedWeapon->WeaponProperties.ReserveAmmo;	
	OnAmmoUse.Broadcast(CurrentAmmo, CurrentReserveAmmo); // Sets HUD Ammo Values
	
	//GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Blue, FString::Printf(TEXT("PlayerController: %s"), *Character->Controller->GetName()));

	
	const USkeletalMeshSocket* HandSocketFP = Character->GetMesh()->GetSocketByName(FName("weaponsocket"));
	if (HandSocketFP)
	{
		// First Person Weapon
		// Attaches Weapon to WeaponSocket when Equip Weapon gets called
		HandSocketFP->AttachActor(EquippedWeapon, Character->GetMesh()); // Correct for First Person
		EquippedWeapon->SetOwner(Character); // Sets Owner
		EquippedWeapon->WeaponMesh->SetOnlyOwnerSee(true);
		SetThirdPersonWeaponVisibility(true);		
			
		// Spawns Third Person Weapon		
		ThirdPersonWeapon = GetWorld()->SpawnActor<ABase_Weapon>(Character->WeaponClass, Character->ThirdPersonMesh->GetSocketTransform(FName("weaponsocket")), FActorSpawnParameters());
		ThirdPersonWeapon->SetWeaponState(EWeaponState::EWS_Equipped);	
		const USkeletalMeshSocket* HandSocketTP = Character->ThirdPersonMesh->GetSocketByName(FName("weaponsocket"));
		
		// Attaches Third Person Weapon
		HandSocketTP->AttachActor(ThirdPersonWeapon, Character->ThirdPersonMesh);
		ThirdPersonWeapon->SetOwner(Character);
		ThirdPersonWeapon->WeaponMesh->SetOwnerNoSee(true);	
		SetThirdPersonWeaponVisibility(true);			
	}		
}

void UCombatComponent::OnRep_ThirdPersonWeaponVisibility()
{
	if (ThirdPersonWeapon)
	{		
		EquippedWeapon->WeaponMesh->SetOnlyOwnerSee(bOwnerCanSee);
		ThirdPersonWeapon->WeaponMesh->SetOwnerNoSee(bOwnerCanSee);	
	}
}

void UCombatComponent::SetThirdPersonWeaponVisibility(bool bVisible)
{
	bOwnerCanSee = bVisible;
	if (ThirdPersonWeapon && EquippedWeapon)
	{
		EquippedWeapon->WeaponMesh->SetOnlyOwnerSee(bVisible);
		ThirdPersonWeapon->WeaponMesh->SetOwnerNoSee(bVisible);
	}
}

void UCombatComponent::Server_Fire_Implementation()
{
	Multicast_Fire();
}

void UCombatComponent::Server_StopFire_Implementation()
{
	Multicast_StopFire();
}

void UCombatComponent::Server_FireShot_Implementation()
{
	Multicast_FireShot();	
}

void UCombatComponent::Server_Reload_Implementation()
{
	Multicast_Reload();
}

void UCombatComponent::Multicast_Fire_Implementation()
{
	if (EquippedWeapon)
	{
		// Loops until TimerHandle is Cleared 
		if (!Character->GetIsDead())
		{
			FireShot();
			GetWorld()->GetTimerManager().SetTimer(TimerHandle_HandleFire, this, &UCombatComponent::FireShot, EquippedWeapon->WeaponProperties.FireRate, true);
		}
	}
}

void UCombatComponent::Multicast_StopFire_Implementation()
{
	if (EquippedWeapon)
	{
		Character->SetIsShooting(false);
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle_HandleFire);
	}
}

void UCombatComponent::Multicast_FireShot_Implementation()
{		
	if (Character && Character->IsLocallyControlled() && !Character->HasAuthority())
	{		
		return;
	}
	LocalFire();		
}

void UCombatComponent::Multicast_Reload_Implementation()
{
	if (EquippedWeapon && CurrentAmmo != EquippedWeapon->WeaponProperties.Ammo)
	{
		Character->SetIsReloading(true);
		CurrentReserveAmmo += CurrentAmmo; // Refil Reserve ammo with leftover from clip
		CurrentAmmo = EquippedWeapon->WeaponProperties.Ammo;
		CurrentReserveAmmo -= CurrentAmmo;
		OnAmmoUse.Broadcast(CurrentAmmo, CurrentReserveAmmo); // Updates HUD
	}
}


