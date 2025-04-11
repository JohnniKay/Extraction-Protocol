// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Base_LoadingScreen.generated.h"

/**
 * 
 */
UCLASS()
class EXTRACTIONPROTOCOL_API UBase_LoadingScreen : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY()
		class UBase_GameInstance* GameInstance;

public:

	virtual void NativePreConstruct() override;

	virtual void NativeConstruct() override;
	
};
