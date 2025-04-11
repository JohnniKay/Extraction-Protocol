// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "BaseAIController.generated.h"

/**
 * 
 */
UCLASS()
class EXTRACTIONPROTOCOL_API ABaseAIController : public AAIController
{
	GENERATED_BODY()

protected:
	ABaseAIController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void BeginPlay() override;

	virtual void OnPossess(APawn* InPawn) override;

private:
	FGenericTeamId TeamID;

	UPROPERTY(VisibleAnywhere, Category = "AI")
		TSubclassOf<UAIPerceptionSystem> PerceviedSense;
public:
	UFUNCTION()
		void PlayerPerceived(AActor* Actor, FAIStimulus Stimulus);

	UFUNCTION()
		void CurrentPerception(const TArray<AActor*>& ActorsNearby);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		class UBehaviorTree* BTAsset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		class UBehaviorTreeComponent* BTComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		class UBlackboardComponent* BBComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		class UAIPerceptionComponent* AIPerception;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		class ABaseCharacter* Target;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		class ABaseAi* AttachedAI;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		float TargetDistance;

	//Distance between players to chase after another player
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		float DistanceToChase;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		bool bIsTargetInRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		bool bIsTargetSet;

		virtual FGenericTeamId GetGenericTeamId() const override { return TeamID; }

		virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;
	
	UFUNCTION(BlueprintCallable, Category = "AI")
		ETeamAttitude::Type GetAttitudeTowards(const AActor* Other) const;

	UFUNCTION()
		virtual float DistanceFromTarget(AActor* TargetActor);
};
