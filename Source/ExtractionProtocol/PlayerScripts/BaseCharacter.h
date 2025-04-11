// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
//Team Id Interface
#include "GenericTeamAgentInterface.h"

// Online systems
#include "Interfaces/OnlineSessionInterface.h"
#include "Blueprint/UserWidget.h"
#include "BaseCharacter.generated.h"

UCLASS(ABSTRACT)
class EXTRACTIONPROTOCOL_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:	
	ABaseCharacter();
	virtual void Tick(float DeltaTime) override;	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void PostInitializeComponents() override;
	
protected:	
	virtual void BeginPlay() override;

#pragma region UI
public:
	UPROPERTY(EditAnywhere, Category = "Menu")
		TSubclassOf<class UBase_PauseMenu> PauseMenuClass;

	UPROPERTY(EditAnywhere, Category = "Menu")
		TSubclassOf<class UBase_EscapeMenu> EscapeMenuClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Menu")
		class UBase_EscapeMenu* EscapeWidgetMenu;

	UPROPERTY(BlueprintReadWrite)
		class UBase_PauseMenu* PauseWidgetMenu;

	UPROPERTY(BlueprintReadWrite)
		class UBase_ControlScheme* ControlSchemeWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Menu")
		TSubclassOf<class UBase_ControlScheme> ControlSchemeClass;

	UPROPERTY(VisibleAnywhere, Category = "Menu")
		bool bIsVisibleEscape;

	UPROPERTY(VisibleAnywhere, Category = "Menu")
		bool bIsVisiblePause;
	
	UFUNCTION()
		virtual void ScoreBoard();
	UFUNCTION()
		virtual	void Escape();
protected:
	// protected UPROPERTY
	// protected FUNCTIONS
private:
	// private UPROPERTY
	// private FUNCTIONS
#pragma endregion

#pragma region HUD
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Menu")
		TSubclassOf<class UBase_HUD> HUDClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UBase_HUD* HUDWidgetMenu;

	class ABase_CharacterHUD* HUD;
	class ABase_PlayerController* PlayerController;
protected:
	// protected UPROPERTY
	// protected FUNCTIONS
private:
	UPROPERTY(EditAnywhere, Category = "OverheadWidget")
		TSubclassOf<class UOverheadWidget> OverheadWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "OverheadWidget", meta = (AllowPrivateAccess = "true"))
		class UWidgetComponent* OverheadWidget;

	UPROPERTY(Replicated)
		class UOverheadWidget* DisplayWidget;
#pragma endregion
	
#pragma region CharacterActions
public:
	// public UPROPERTY
	// public FUNCTIONS
protected:
	void MoveForward(const float Value);
	void MoveRight(const float Value);
	void LookUp(const float Value);
	void LookRight(const float Value);
	UFUNCTION()
	void Death(float CurrentHealth, float MaxHealth);
	UFUNCTION()
	void Hurt(float CurrentHealth, float MaxHealth);
	void RevivePlayer();	
	void EquipButtonPressed();
	void CrouchButtonPressed();
	void AimOffset(float DeltaTime);
	void StartFire();
	void StopFire();
	void Reload();
	void Restock();
	void ControlSchemeOverlay();
private:
	UPROPERTY(ReplicatedUsing = OnRep_OverlappingWeapon)
		class ABase_Weapon* OverlappingWeapon;

	// Must be UFUNCTION
	// If value is passed, it will be the last value before the replication happened.
	// 
	// Ex: OverlappingWeapon = nullptr. As soon as it changes on the server, the new value is replicated down to clients. 
	// If we have a weapon input parameter, then the value inside the function
	//		 for the LastWeapon will be the last value of overlapping weapon before variable was replicated
	// 
	// Rep Notifies do NOT get called on sever, only when the variable replicates
	// Replication only works one way: Server -> Client
	UFUNCTION()
		void OnRep_OverlappingWeapon(ABase_Weapon* LastWeapon);


	UFUNCTION(Server, Reliable)
		void ServerEquipButtonPressed();

	float AO_Yaw;
	float AO_Pitch;
	UPROPERTY(Replicated)
	bool bIsDead;
	bool bIsHurt;
	bool bIsShooting;
	bool bIsReloading;
	bool bOverlayActive;
#pragma endregion

#pragma region CharacterComponents
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		class UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		class UCameraComponent* DeathCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
		class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		class USkeletalMeshComponent* ThirdPersonMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "HealthComponent")
		class UHealthComponent* HealthComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		TSubclassOf<ABase_Weapon> WeaponClass;
			
	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Replicated, Category = "State")
		TArray<class ABase_Weapon*> Weapons;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category = "State")
		int32 CurrentIndex = 0;
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Configurations")
		TArray<TSubclassOf<class ABase_Weapon>> DefaultWeapons;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UBaseCharacterAnim* AnimBP;
private:
	UPROPERTY(VisibleAnywhere)
		class UCombatComponent* Combat;

	
#pragma endregion		
	
public:

	// Getters and Setters
		ABase_Weapon* GetEquippedWeapon();
				bool IsWeaponEquipped();
	FORCEINLINE float GetAO_Yaw() const { return AO_Yaw;	}
	FORCEINLINE float GetAO_Pitch()	const { return AO_Pitch; }
	FORCEINLINE bool GetIsDead() const { return bIsDead; }
	FORCEINLINE bool GetIsHurt() const { return bIsHurt; }
	FORCEINLINE bool GetIsShooting() const { return bIsShooting; }
	FORCEINLINE bool GetIsReloading() const { return bIsReloading; }

				void SetOverlappingWeapon(ABase_Weapon* Weapon);
	FORCEINLINE void SetIsShooting(bool bShooting) { bIsShooting = bShooting; }
	FORCEINLINE void SetIsReloading(bool bReloading) { bIsReloading = bReloading; }
};
