// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Base_Direction.generated.h"

USTRUCT(BlueprintType)
struct FDirectionStruct
{

	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Compass")
		FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Compass")
		int32 WorldRotation = 0;


};

/**
 * 
 */
UCLASS()
class EXTRACTIONPROTOCOL_API UBase_Direction : public UUserWidget
{
	GENERATED_BODY()
	
public:

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Compass")
	//	struct FDirectionStruct DirectionInfo;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Compass", meta = (BindWidget))
	//	class UTextBlock* Text;


public:

	virtual void NativePreConstruct();
	virtual void NativeConstruct();
};
