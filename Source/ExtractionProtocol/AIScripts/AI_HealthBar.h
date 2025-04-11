// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AI_HealthBar.generated.h"

/**
 * 
 */
UCLASS()
class EXTRACTIONPROTOCOL_API UAI_HealthBar : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Health", meta = (BindWidget))
		class UProgressBar* HealthBar;

	UFUNCTION()
		void SetHealth(float CurrentHealth, float MaxHealth);
};
