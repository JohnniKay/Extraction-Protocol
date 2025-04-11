// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseAi.h"
#include "GruntAI.generated.h"

/**
 * 
 */
UCLASS()
class EXTRACTIONPROTOCOL_API AGruntAI : public ABaseAi
{
	GENERATED_BODY()
	

public:
	AGruntAI();

protected:
	virtual void BeginPlay() override;

	virtual void MeleePlayer(FHitResult OutHit) override;

	virtual void MeleeAttackFinished() override;
	
	virtual void CharacterDeath(float CurrentHealth, float MaxHealth) override;

	virtual void CharacterDeathFinished() override;

	virtual void SetController() override;

public:

};
