// Fill out your copyright notice in the Description page of Project Settings.

// Created Classes
#include "BaseCharacter.h"
#include "BaseCharacterAnim.h"
#include "../Weapons/Base_Weapon.h"
#include "../Weapons/WeaponComponents/CombatComponent.h"
#include "../ExtractionProtocol.h"
#include "../UI/Base_PauseMenu.h"
#include "../UI/Base_EscapeMenu.h"
#include "../UI/Base_HUD.h"
#include "../UI/Base_ControlScheme.h"
#include "../UI/OverheadWidget.h"
#include "../Component/HealthComponent.h"
#include "../UI/Base_CharacterHUD.h"
#include "../Other/Base_PlayerController.h"

// Unreal Classes
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Camera/PlayerCameraManager.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/SpringArmComponent.h"


// Online Systems
#include "Net/UnrealNetwork.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"

// Sets default values				
ABaseCharacter::ABaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(GetCapsuleComponent());
	Camera->SetIsReplicated(true);
	Camera->bUsePawnControlRotation = true; // Always facing direction of pawn controller
	
	//Camera->SetupAttachment(GetMesh(), FName("spine_03"));

	GetMesh()->SetupAttachment(Camera);
	GetMesh()->CastShadow = false;

	ThirdPersonMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ThirdPerson"));
	ThirdPersonMesh->SetupAttachment(GetCapsuleComponent());
	ThirdPersonMesh->CastShadow = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(ThirdPersonMesh);
	SpringArm->bUsePawnControlRotation = true;

	DeathCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("DeathCamera"));
	DeathCamera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	DeathCamera->bUsePawnControlRotation = false;
	DeathCamera->SetActive(false);

	// UI
	bIsVisibleEscape = false;
	bIsVisiblePause = false;
	bOverlayActive = false;

	// Components dont need to be register in the GetLifetimeReplicatedProps they just need to be set to replciate
	Combat = CreateDefaultSubobject<UCombatComponent>(TEXT("CombatComponent"));
	Combat->SetIsReplicated(true);

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	HealthComponent->SetIsReplicated(true);
	HealthComponent->SetMaxHealth(200);
	
	// Enables Crouching
	GetCharacterMovement()->NavAgentProps.bCanCrouch;	

	// OverheadWidget - Currently: Displays Name - Future: Displays Distance from other player
	// Sets Widget Class in Editor. 
	OverheadWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("OverheadWidget"));
	OverheadWidget->SetupAttachment(RootComponent);
	OverheadWidget->SetWidgetSpace(EWidgetSpace::Screen);
	OverheadWidget->SetDrawAtDesiredSize(true);	
	OverheadWidget->SetOwnerNoSee(true);
}

void ABaseCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Notify Condition is set so the OverlappingWeapon is only replicated to the owner of the pawn
	DOREPLIFETIME_CONDITION(ABaseCharacter, OverlappingWeapon, COND_OwnerOnly);
	DOREPLIFETIME(ABaseCharacter, bIsDead);

}

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	// Player Controller
	PlayerController = Cast<ABase_PlayerController>(Controller);
	if (PlayerController)
	{
		PlayerController->SetHealth(HealthComponent->CurrentHealth, HealthComponent->MaxHealth);
		HealthComponent->OnDamage.AddDynamic(PlayerController, &ABase_PlayerController::SetHealth);
		HealthComponent->OnDeath.AddDynamic(PlayerController, &ABase_PlayerController::SetHealth);
		Combat->OnAmmoUse.AddDynamic(PlayerController, &ABase_PlayerController::SetAmmo);
	}

	// Animation 
	AnimBP = Cast<UBaseCharacterAnim>(GetMesh()->GetAnimInstance());
	if (AnimBP)
	{
		AnimBP->OnReloadWeapon.AddDynamic(Combat, &UCombatComponent::ReloadFinished);
	}

	// Player Name Widget	
	DisplayWidget = Cast<UOverheadWidget>(OverheadWidget->GetUserWidgetObject());
	if (DisplayWidget)
	{
		DisplayWidget->DisplayPlayerName(this);
	}	

	HealthComponent->OnDeath.AddDynamic(this, &ABaseCharacter::Death);
	ControlSchemeWidget = CreateWidget<UBase_ControlScheme>(PlayerController, ControlSchemeClass);

	// Hides head on First Person Mesh
	GetMesh()->HideBoneByName(TEXT("neck_01"), PBO_None);	
	
}

void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimOffset(DeltaTime);
}

void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(FName("MoveForward"), this, &ABaseCharacter::MoveForward);
	PlayerInputComponent->BindAxis(FName("MoveRight"), this, &ABaseCharacter::MoveRight);
	PlayerInputComponent->BindAxis(FName("LookUp"), this, &ABaseCharacter::LookUp);
	PlayerInputComponent->BindAxis(FName("LookRight"), this, &ABaseCharacter::LookRight);

	PlayerInputComponent->BindAction(FName("Jump"), IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Equip", IE_Pressed, this, &ABaseCharacter::EquipButtonPressed);	
	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &ABaseCharacter::CrouchButtonPressed);
	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &ABaseCharacter::StartFire);
	PlayerInputComponent->BindAction("Shoot", IE_Released, this, &ABaseCharacter::StopFire);
	PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &ABaseCharacter::Reload);
	PlayerInputComponent->BindAction("Revive", IE_Pressed, this, &ABaseCharacter::RevivePlayer);
	PlayerInputComponent->BindAction("Restock", IE_Pressed, this, &ABaseCharacter::Restock);
	PlayerInputComponent->BindAction(FName("Escape"), EInputEvent::IE_Pressed, this, &ABaseCharacter::Escape);
	PlayerInputComponent->BindAction(FName("Scoreboard"), EInputEvent::IE_Pressed, this, &ABaseCharacter::ScoreBoard);
	PlayerInputComponent->BindAction("ControlScheme", IE_Pressed, this, &ABaseCharacter::ControlSchemeOverlay);
}

void ABaseCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (Combat)
	{
		Combat->Character = this;
	}
}

void ABaseCharacter::MoveForward(const float Value)
{
	const FVector& Direction = FRotationMatrix(FRotator(0.f, GetControlRotation().Yaw, 0.f)).GetUnitAxis(EAxis::X);
	AddMovementInput(Direction, Value);
}

void ABaseCharacter::MoveRight(const float Value)
{
	const FVector& Direction = FRotationMatrix(FRotator(0.f, GetControlRotation().Yaw, 0.f)).GetUnitAxis(EAxis::Y);
	AddMovementInput(Direction, Value);
}

void ABaseCharacter::LookUp(const float Value)
{
	AddControllerPitchInput(Value);
}

void ABaseCharacter::LookRight(const float Value)
{
	AddControllerYawInput(Value);
}

void ABaseCharacter::Death(float CurrentHealth, float MaxHealth)
{
	if (PlayerController)
	{		
		bIsDead = true;
		Combat->StopFire(); // Clears Timer Handle loop of automatic weapons
		GetCharacterMovement()->StopMovementImmediately();
		
		// GetCharacterMovement()->GravityScale = 0.f;		 
		// GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECR_Ignore);	

		// Sets Camera Switch
		Camera->SetActive(false);		
		DeathCamera->SetActive(true);
		// Sets Mesh Switch
		GetMesh()->SetOwnerNoSee(true);
		ThirdPersonMesh->SetOwnerNoSee(false);
		// Hides Weapon Mesh
		if(Combat->EquippedWeapon) { Combat->EquippedWeapon->WeaponMesh->SetOwnerNoSee(true); }		
		// Sets Movement 
		GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);		
		GetCharacterMovement()->bOrientRotationToMovement = false;
		bUseControllerRotationYaw = false;				
	}	
}

void ABaseCharacter::Hurt(float CurrentHealth, float MaxHealth)
{
	// Handle Hurt animation
	if (PlayerController)
	{
		bIsHurt = true;
	}	
}

void ABaseCharacter::RevivePlayer()
{
	bIsDead = false;	
	
	// Set Health
	//HealthComponent->CurrentHealth = HealthComponent->MaxHealth;
	HealthComponent->SetMaxHealth(200);
	PlayerController->SetHealth(HealthComponent->CurrentHealth, HealthComponent->MaxHealth);
	OnTakeAnyDamage.AddDynamic(HealthComponent, &UHealthComponent::HandleDamage);
	// Sets Camera Switch
	Camera->SetActive(true);
	DeathCamera->SetActive(false);
	// Sets Mesh Switch
	GetMesh()->SetOwnerNoSee(false);
	ThirdPersonMesh->SetOwnerNoSee(true);
	// Shows Weapon Mesh
	Combat->EquippedWeapon->WeaponMesh->SetOwnerNoSee(false);
	// Sets Movement 
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationYaw = true;	
}

void ABaseCharacter::EquipButtonPressed()
{
	// Only Server should call EquipWeapon
	if (Combat)
	{
		// If owner has authority, call Equip Weapon directly
		if (HasAuthority())
		{
			Combat->EquipWeapon(OverlappingWeapon);							
		}
		// Otherwise send the RPC
		else
		{
			ServerEquipButtonPressed();
		}		
	}
}

void ABaseCharacter::ServerEquipButtonPressed_Implementation()
{
	// No need to call HasAuthority because the RPC will only be called on the server due to UFUNCTION(Server)
	if (Combat)
	{
		Combat->EquipWeapon(OverlappingWeapon);
	}
}

void ABaseCharacter::CrouchButtonPressed()
{
	if (bIsCrouched)
	{
		UnCrouch();
	}
	else
	{
		Crouch();
	}
}

void ABaseCharacter::AimOffset(float DeltaTime)
{
	if (Combat && Combat->EquippedWeapon == nullptr) return;

	if (GetBaseAimRotation().Pitch >= 180.f)
	{
		AO_Pitch = GetBaseAimRotation().Pitch - 360.f;		
	}
	else
	{
		AO_Pitch = GetBaseAimRotation().Pitch;
	}
}

void ABaseCharacter::StartFire()
{
	Combat->StartFire();	
}

void ABaseCharacter::StopFire()
{
	Combat->StopFire();	
}

void ABaseCharacter::Reload()
{
	Combat->Reload();
}

void ABaseCharacter::Restock()
{
	Combat->Restock();
}

void ABaseCharacter::ControlSchemeOverlay()
{
	if (!bOverlayActive)
	{
		bOverlayActive = true;
		if (ControlSchemeWidget) { ControlSchemeWidget->AddToViewport(); }
	}
	else
	{
		if (ControlSchemeWidget) { ControlSchemeWidget->RemoveFromParent(); }
		bOverlayActive = false;
	}
}

void ABaseCharacter::ScoreBoard()
{
	//PlayerController = Cast<APlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	
	if (!bIsVisiblePause)
	{		
		if (IsValid(PauseMenuClass))
		{
			PauseWidgetMenu = CreateWidget<UBase_PauseMenu>(PlayerController, PauseMenuClass);
			//GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Blue, FString::Printf(TEXT("Created Widget %s")));
		}
		if (PauseWidgetMenu)
		{
			PauseWidgetMenu->AddToViewport();
			
			UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(PlayerController, PauseWidgetMenu, EMouseLockMode::DoNotLock);
			//this->GetCharacterMovement()->StopActiveMovement();
			//DisableInput(PlayerController);
			
			bIsVisiblePause = true;
		}
		else
		{
			UE_LOG(Game, Error, TEXT("PauseWidgetMenu is Invalid"));			
		}
	}
	else
	{		
		PauseWidgetMenu->RemoveFromParent();
		UWidgetBlueprintLibrary::SetInputMode_GameOnly(PlayerController);
		this->GetCharacterMovement()->ResetMoveState();
		
		//EnableInput(PlayerController);
		bIsVisiblePause = false;
	}
}

void ABaseCharacter::Escape()
{
	//PlayerController = Cast<APlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	if (!bIsVisibleEscape)
	{
		if (IsValid(EscapeMenuClass))
		{
			EscapeWidgetMenu = CreateWidget<UBase_EscapeMenu>(PlayerController, EscapeMenuClass);
		}
		if (EscapeWidgetMenu)
		{
			EscapeWidgetMenu->AddToViewport();
			UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(PlayerController, EscapeWidgetMenu, EMouseLockMode::DoNotLock);
			PlayerController->bShowMouseCursor = true;
			bIsVisibleEscape = true;
		}
		else
		{
			UE_LOG(Game, Error, TEXT("EscapeWidgetMenu is Invalid"));
		}
	}
	else
	{
		EscapeWidgetMenu->RemoveFromParent();
		UWidgetBlueprintLibrary::SetInputMode_GameOnly(PlayerController);
		PlayerController->bShowMouseCursor = false;
		bIsVisibleEscape = false;
	}
}

void ABaseCharacter::SetOverlappingWeapon(ABase_Weapon* Weapon)
{
	if (OverlappingWeapon)
	{
		OverlappingWeapon->ShowPickupWidget(false);
	}

	OverlappingWeapon = Weapon;

	// Equals true if function is called on the character that is being controlled by the player who is hosting the game on the server
	// None of the Clients will be Owners of this character 
	if (IsLocallyControlled())
	{		 
		if (OverlappingWeapon)
		{
			OverlappingWeapon->ShowPickupWidget(true);
		}
	}
}

void ABaseCharacter::OnRep_OverlappingWeapon(ABase_Weapon* LastWeapon)
{
	if (OverlappingWeapon)
	{
		OverlappingWeapon->ShowPickupWidget(true);
	}

	if (LastWeapon)
	{
		// If we end overlap, the overlapping weapon will be set to null resulting in the above if statement return false but our last value
		//			for overlapping weapon will still have the pointer to the weapon we stopped overlapping
		LastWeapon->ShowPickupWidget(false);
	}
}

bool ABaseCharacter::IsWeaponEquipped()
{
	return (Combat && Combat->EquippedWeapon);
}

ABase_Weapon* ABaseCharacter::GetEquippedWeapon()
{
	if (Combat == nullptr) return nullptr;
	return Combat->EquippedWeapon;
}
