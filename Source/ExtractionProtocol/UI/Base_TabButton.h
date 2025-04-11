// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../Other/Delegates.h"
#include "Base_TabButton.generated.h"

/**
 * 
 */
UCLASS()
class EXTRACTIONPROTOCOL_API UBase_TabButton : public UUserWidget
{
	GENERATED_BODY()

public:

	// Border
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default", meta = (BindWidget))
		class UBorder* Border;
	// Button
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default", meta = (BindWidget))
		class UButton* Button;
	// Text (Info)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default", meta = (BindWidget))
		class UTextBlock* Info;
	// Text (ButtonText)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default", meta = (BindWidget))
		FText ButtonText;
	// Event Dispatcher
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Events")
		FEventDispatcher OnButtonClicked;
	//Button Clicked sound
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Menu")
		class USoundBase* ClickSound;
	//Button Hovered sound
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Menu")
		class USoundBase* HoveredSound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Menu", meta = (BindWidget))
		class UWidgetAnimation* Hover1;


public:

	virtual void NativePreConstruct() override;

	virtual void NativeConstruct() override;

	UFUNCTION()
		void OnClicked();

	UFUNCTION()
		void OnHovered();

	UFUNCTION()
		void OnUnhovered();
	
};
