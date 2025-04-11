// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base_DirectionStruct.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct EXTRACTIONPROTOCOL_API FBase_DirectionStruct
{

	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Compass")
		FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Compass")
		int32 WorldRotation = 0;

	FBase_DirectionStruct();
	~FBase_DirectionStruct();
};
