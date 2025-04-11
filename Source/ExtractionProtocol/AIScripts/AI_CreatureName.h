// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AI_CreatureName.generated.h"

/**
 * 
 */
UCLASS()
class EXTRACTIONPROTOCOL_API UAI_CreatureName : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Name", meta = (BindWidget))
		class UTextBlock* CreatureName;

	UFUNCTION()
		void SetText(FText _CreatureName);
};
