// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../Other/Delegates.h"
#include "HealthComponent.generated.h"

/**
 *
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class EXTRACTIONPROTOCOL_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Health")
		float MaxHealth;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Health")
		float CurrentHealth;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Health")
		float ArmorValue;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Health")
		FHealthChange OnDeath;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Health")
		FHealthChange OnDamage;

	class AActor* Owner;

	UFUNCTION()
	void HandleDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamagedCauser);

	UFUNCTION()
		void SetMaxHealth(float _MaxHealth);

	UFUNCTION()
		void SetArmorValue(float _ArmorValue);
};
