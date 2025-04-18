// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OverheadWidget.generated.h"

/**
 * 
 */
UCLASS()
class EXTRACTIONPROTOCOL_API UOverheadWidget : public UUserWidget
{
	GENERATED_BODY()

public: 
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* DisplayName;

	UFUNCTION(BlueprintCallable)
	void DisplayPlayerName(APawn* InPawn);
	FString GetPlayerNetRole(APawn* InPawn);		
};
