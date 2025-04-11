// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseAi.generated.h"

USTRUCT(BlueprintType)
struct FCreatureAttributes {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float Health = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float WalkSpeed = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float MeleeDamage = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float MeleeRange = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float DetectionRange = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float ArmorValue = 0.f;
};

/**
 *
 */
UCLASS(ABSTRACT)
class EXTRACTIONPROTOCOL_API ABaseAi : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseAi();

	//Components 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attributes|Components")
		class UHealthComponent* HealthComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes")
		FCreatureAttributes CreatureStruct;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes")
		class UBaseAIAnim* AnimBP;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes|AI")
		class ABaseAIController* AIController;

	UPROPERTY(VisibleAnywhere, Category = "Attributes|AI")
		class UBrainComponent* BrainComponent;

	UPROPERTY(VisibleAnywhere, Category = "Attributes|AI")
		class UBlackboardComponent* BBComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes|AI")
		TArray<AActor*> AllPlayers;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes|AI")
		TArray<int> AllAttackersNums;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes|AI")
		bool bIsValidPlayer{ false };

	//Bool for animation when dead
	//UPROPERTY(Replicated)
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadOnly, Category = "Attributes|AI")
	bool bIsDead;
	
	//Bool for animation when hurt
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadOnly, Category = "Attributes|AI")
	bool bIsHurt;
	
	//Timer to change bIsHurt to false
	FTimerHandle TimerHandle;

	//Bool for animation when attacking
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadOnly, Category = "Attributes|AI")
	bool bIsAttacking;

#pragma region HUD Over Creature
	UPROPERTY(EditAnywhere, Category = "Attributes|HUD")
		class UWidgetComponent* OverHeadHealthBar;
	
	UPROPERTY(EditAnywhere, Category = "Attributes|HUD")	
		TSubclassOf<class UAI_HealthBar> OverHeadHealthBarClass;

	UPROPERTY(Replicated, EditAnywhere, Category = "Attributes|HUD")
		class UAI_HealthBar* HealthBarWidget;

	UPROPERTY(EditAnywhere, Category = "Attributes|HUD")
		class UWidgetComponent* OverHeadName;

	UPROPERTY(Replicated, EditAnywhere, Category = "Attributes|HUD")
		class UAI_CreatureName* NameWidget;

	UPROPERTY(EditAnywhere, Category = "Attributes|HUD")
		TSubclassOf<class UAI_CreatureName> OverHeadNameClass;

	UPROPERTY(Replicated, EditAnywhere, Category = "Attributes|HUD")
		ESlateVisibility EVisible;

	FTimerHandle HUDHandle;
#pragma endregion
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	//virtual void PossessedBy(AController* NewController) override;
public:
	//Getters and Setters
	FORCEINLINE bool GetIsDead() const { return bIsDead; }
	FORCEINLINE bool GetIsHurt() const { return bIsHurt; }
	FORCEINLINE bool GetIsAttacking() const { return bIsAttacking; }

	UFUNCTION()
		virtual void CharacterDeath(float CurrentHealth, float MaxHealth);

	UFUNCTION()
		virtual void CharacterHurt(float CurrentHealth, float MaxHealth);

	UFUNCTION()
	virtual void CharacterDeathFinished();

	UFUNCTION()
		virtual void CharacterNoLongerHurt();

	virtual void MeleePlayer(FHitResult OutHit);
	
	UFUNCTION()
	virtual void MeleeAttackFinished();

	virtual void SetReferencesAndBind();

	virtual void SetController();

	virtual bool IsTargetInRange(AActor* Target);

	virtual void TurnOffHud();
};