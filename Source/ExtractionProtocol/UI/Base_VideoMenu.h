// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Other/Delegates.h"
#include "Blueprint/UserWidget.h"
#include "Base_VideoMenu.generated.h"

/**
 * 
 */
UCLASS()
class EXTRACTIONPROTOCOL_API UBase_VideoMenu : public UUserWidget
{
	GENERATED_BODY()
	
public:

	//Sound menu back button
	UPROPERTY(BlueprintReadWrite, Category = "Button", meta = (BindWidget))
		class UBase_Button* BackButton;

	UPROPERTY(BlueprintReadWrite, Category = "Button", meta = (BindWidget))
		class UBase_Button* SoundButton;

	UPROPERTY(BlueprintReadWrite, Category = "Button", meta = (BindWidget))
		class UBase_Button* ControlsButton;

	UPROPERTY(BlueprintReadWrite, Category = "Button", meta = (BindWidget))
		class UBase_Button* SaveSettingsButton;

	//Settings Buttons
	//Screen Size
	UPROPERTY(BlueprintReadWrite, Category = "Button", meta = (BindWidget))
		class UBase_Button* FullscreenButton;

	UPROPERTY(BlueprintReadWrite, Category = "Button", meta = (BindWidget))
		class UBase_Button* WindowedButton;

	//Display Resolution
	UPROPERTY(BlueprintReadWrite, Category = "Button", meta = (BindWidget))
		class UBase_Button* DisplayOneButton;

	UPROPERTY(BlueprintReadWrite, Category = "Button", meta = (BindWidget))
		class UBase_Button* DisplayTwoButton;

	UPROPERTY(BlueprintReadWrite, Category = "Button", meta = (BindWidget))
		class UBase_Button* DisplayThreeButton;

	UPROPERTY(BlueprintReadWrite, Category = "Button", meta = (BindWidget))
		class UBase_Button* DisplayFourButton;

	//FPS
	UPROPERTY(BlueprintReadWrite, Category = "Button", meta = (BindWidget))
		class UBase_Button* FPSOneButton;

	UPROPERTY(BlueprintReadWrite, Category = "Button", meta = (BindWidget))
		class UBase_Button* FPSTwoButton;

	UPROPERTY(BlueprintReadWrite, Category = "Button", meta = (BindWidget))
		class UBase_Button* FPSThreeButton;

	UPROPERTY(BlueprintReadWrite, Category = "Button", meta = (BindWidget))
		class UBase_Button* FPSFourButton;

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

	//Controls Menu 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Menu")
		TSubclassOf<class UBase_ControlsMenu> ControlsMenuClass;

	UPROPERTY(BlueprintReadWrite, Category = "Menu")
		class UBase_ControlsMenu* ControlsWidgetMenu;

	//Save Settings Menu 
	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Menu")
	//	TSubclassOf<class UBase_ConfirmationMenu> SaveSettingsMenuClass;

	//UPROPERTY(BlueprintReadWrite, Category = "Menu")
	//	class UBase_ConfirmationMenu* SaveSettingsWidgetMenu;

	//GameInstance
	UPROPERTY(BlueprintReadWrite, Category = "Game Instance")
		class UBase_GameInstance* GameInstance;

	//Video variables
	UPROPERTY()
		bool FullscreenVideo;

	UPROPERTY()
		bool WindowedVideo;

	UPROPERTY()
		FIntPoint Resolution;

	UPROPERTY()
		float FrameRate;

public:

	virtual void NativePreConstruct();

	virtual void NativeConstruct();

	//Clicked Button
	UFUNCTION()
		void OnSoundButtonClicked();

	UFUNCTION()
		void OnControlsButtonClicked();

	UFUNCTION()
		void OnBackButtonClicked();

	UFUNCTION()
		void OnSaveSettingsButtonClicked();

	//Screen Size
	UFUNCTION()
		void OnFullscreenButtonClicked();

	UFUNCTION()
		void OnWindowedButtonClicked();

	//Display Resolution
	UFUNCTION()
		void OnResolutionOneButtonClicked();

	UFUNCTION()
		void OnResolutionTwoButtonClicked();

	UFUNCTION()
		void OnResolutionThreeButtonClicked();

	UFUNCTION()
		void OnResolutionFourButtonClicked();

	//FPS
	UFUNCTION()
		void OnFPSOneButtonClicked();

	UFUNCTION()
		void OnFPSTwoButtonClicked();

	UFUNCTION()
		void OnFPSThreeButtonClicked();

	UFUNCTION()
		void OnFPSFourButtonClicked();

	//Screen Size Enabled
	UFUNCTION()
		void ScreenSizeEnabled(bool Fullscreen, bool Windowed);

	//Screen Size Enabled
	UFUNCTION()
		void DisplayResolutionEnabled(bool ResOne, bool ResTwo, bool ResThree, bool ResFour);

	//Screen Size Enabled
	UFUNCTION()
		void FPSEnabled(bool FPSOne, bool FPSTwo, bool FPSThree, bool FPSFour);

	UFUNCTION()
		void LoadSettings();

};
