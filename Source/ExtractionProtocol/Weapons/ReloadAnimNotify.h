// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "ReloadAnimNotify.generated.h"

/**
 * 
 */
UCLASS()
class EXTRACTIONPROTOCOL_API UReloadAnimNotify : public UAnimNotify
{
	GENERATED_BODY()

public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
		
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Animation")
		class UBaseCharacterAnim* ReloadNotify;
};
