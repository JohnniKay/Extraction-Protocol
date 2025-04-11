// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Base_CreditsMenu.generated.h"

/**
 * 
 */
UCLASS()
class EXTRACTIONPROTOCOL_API UBase_CreditsMenu : public UUserWidget
{
	GENERATED_BODY()
	
public:

	//Credits menu back button
	UPROPERTY(BlueprintReadWrite, Category = "Button", meta = (BindWidget))
		class UBase_Button* BackButton;

	//Scroll Animation
	UPROPERTY(Transient, meta = (BindWidgetAnim))
		class UWidgetAnimation* ScrollAnimation;

	//Main Menu 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Menu")
		TSubclassOf<class UBase_MainMenu> MainMenuClass;

	UPROPERTY(BlueprintReadWrite, Category = "Menu")
		class UBase_MainMenu* MainWidgetMenu;

public:

	virtual void NativeConstruct();

	UFUNCTION()
		void OnBackButtonClicked();
};
