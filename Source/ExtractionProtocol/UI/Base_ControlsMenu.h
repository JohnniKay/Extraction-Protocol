// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Base_ControlsMenu.generated.h"

/**
 * 
 */
UCLASS()
class EXTRACTIONPROTOCOL_API UBase_ControlsMenu : public UUserWidget
{
	GENERATED_BODY()
	
public:
	//Options Button
	UPROPERTY(BlueprintReadWrite, Category = "Button", meta = (BindWidget))
		class UBase_Button* BackButton;

	UPROPERTY(BlueprintReadWrite, Category = "Button", meta = (BindWidget))
		class UBase_Button* VideoButton;

	UPROPERTY(BlueprintReadWrite, Category = "Button", meta = (BindWidget))
		class UBase_Button* SoundButton;

	//Main Menu 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Menu")
		TSubclassOf<class UBase_MainMenu> MainMenuClass;

	UPROPERTY(BlueprintReadWrite, Category = "Menu")
		class UBase_MainMenu* MainWidgetMenu;

	//Sound Menu 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Menu")
		TSubclassOf<class UBase_SoundMenu> SoundMenuClass;

	UPROPERTY(BlueprintReadWrite, Category = "Menu")
		class UBase_SoundMenu* SoundWidgetMenu;

	//Video Menu 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Menu")
		TSubclassOf<class UBase_VideoMenu> VideoMenuClass;

	UPROPERTY(BlueprintReadWrite, Category = "Menu")
		class UBase_VideoMenu* VideoWidgetMenu;

public:

	virtual void NativeConstruct();

	UFUNCTION()
		void OnVideoButtonClicked();

	UFUNCTION()
		void OnSoundButtonClicked();

	UFUNCTION()
		void OnBackButtonClicked();
};
