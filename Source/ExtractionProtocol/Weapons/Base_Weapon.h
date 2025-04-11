// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Base_Weapon.generated.h"


USTRUCT(BlueprintType)
struct FWeaponProperties
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Damage = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float FireRate = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Ammo = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float ReserveAmmo = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float ReloadTime = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float ArmorPen = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float AoE_Range = 0.f;
};

UENUM(BlueprintType)
enum class EWeaponState : uint8
{
	EWS_Initial UMETA(DisplayName = "InitialState"),
	EWS_Equipped UMETA(DisplayName = "Equipped"),
	EWS_Dropped UMETA(DisplayName = "Dropped"),
	EWS_Max UMETA(DisplayName = "Default")
};

UCLASS()
class EXTRACTIONPROTOCOL_API ABase_Weapon : public AActor
{
	GENERATED_BODY()
	
public:		
	ABase_Weapon();
	virtual void Tick(float DeltaTime) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;	
protected:	
	virtual void BeginPlay() override;
private:

#pragma region Weapon Locker Functions
	
public:
	void ShowPickupWidget(bool bShowWidget);
protected:
	UFUNCTION()
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	virtual void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
private:
	UPROPERTY(VisibleAnywhere, Category = "Weapon Properties")
		class USphereComponent* AreaSphere;

	UPROPERTY(VisibleAnywhere, Category = "Weapon Properties")
		class UWidgetComponent* PickupWidget;

#pragma endregion

#pragma region Weapon Configurations
public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Configurations")
		class USoundBase* FireSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Configurations")
		class USoundBase* DryFireSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Configurations")
		class USoundBase* ReloadSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Configurations")
		class USoundBase* BodyImpactSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Configurations")
		class USoundBase* MissedImpactSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Configurations")
		class UAnimSequence* FireAnimtion;	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Configurations")
		class UParticleSystem* MuzzleParticles;	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Configurations")
		FWeaponProperties WeaponProperties;

	UPROPERTY(EditAnywhere, Category = "Weapon Configurations")
		class UTexture2D* Reticle;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category = "State")
		class ABaseCharacter* CurrentOwner;

	UPROPERTY(VisibleAnywhere, Category = "Weapon Properties")
		class USkeletalMeshComponent* WeaponMesh;	
private:

	UPROPERTY(ReplicatedUsing = OnRep_WeaponState, VisibleAnywhere, Category = "Weapon Properties")
		EWeaponState WeaponState;

	UFUNCTION()
		void OnRep_WeaponState();

#pragma endregion

// Getters and Setters
public:
	void SetWeaponState(EWeaponState State);
	FORCEINLINE USphereComponent* GetAreaSphere() const { return AreaSphere; }
	FORCEINLINE USkeletalMeshComponent* GetWeaponMesh() const {	return WeaponMesh; }
};
