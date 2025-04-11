// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "WanderAroundPoint.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class EXTRACTIONPROTOCOL_API UWanderAroundPoint : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		float Radius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FBlackboardKeySelector OutputVector;

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
