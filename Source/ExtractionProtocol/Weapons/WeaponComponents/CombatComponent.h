// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CombatComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FAmmoChange, float, CurrentAmmo, float, CurrentAmmoReserve);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class EXTRACTIONPROTOCOL_API UCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCombatComponent();
	// Friend classes get access to all functions and variables
	friend class ABaseCharacter;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;	

protected:
	virtual void BeginPlay() override;
	
private: 
	class ABaseCharacter* Character;
	class ABase_PlayerController* Controller;
	
#pragma region Weapon Actions
public:
	void EquipWeapon(class ABase_Weapon* WeaponToEquip);	

protected:
	FTimerHandle TimerHandle_HandleFire;
	void StartFire();
	void StopFire();
	void FireShot();
	void Reload();
	void LocalFire();
	UFUNCTION()
	void ReloadFinished();
	void Restock();
	UFUNCTION(Server, Reliable)
		void Server_Fire();
	UFUNCTION(Server, Reliable)
		void Server_StopFire();
	UFUNCTION(Server, Reliable)
		void Server_FireShot();
	UFUNCTION(Server, Reliable)
		void Server_Reload();
	UFUNCTION(NetMulticast, Reliable)
		void Multicast_Fire();
	UFUNCTION(NetMulticast, Reliable)
		void Multicast_StopFire();
	UFUNCTION(NetMulticast, Reliable)
		void Multicast_FireShot();
	UFUNCTION(NetMulticast, Reliable)
		void Multicast_Reload();
	
	// OnRep Notify to tell when to hide ThirdPersonWeaponMesh
	UPROPERTY(ReplicatedUsing = OnRep_ThirdPersonWeaponVisibility)
	bool bOwnerCanSee;
	UFUNCTION()
	void OnRep_ThirdPersonWeaponVisibility();
		
private:
	UPROPERTY(Replicated)
		class ABase_Weapon* EquippedWeapon;

	UPROPERTY(Replicated)
		class ABase_Weapon* ThirdPersonWeapon;
	// Fucntion to set ThirdPersonWeaponVisibility
	void SetThirdPersonWeaponVisibility(bool bVisible);
#pragma endregion

#pragma region Ammo Logic
public:
	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadWrite, Category = "Ammo")
		FAmmoChange OnAmmoUse;
protected:
	// protected UPROPERTY
	// protected FUNCTIONS
private:	
	/*UPROPERTY(Replicated)
		bool bAiming;*/
	UPROPERTY(Replicated)
	float CurrentAmmo;
	UPROPERTY(Replicated)
	float CurrentReserveAmmo;
#pragma endregion


};
