// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Base_SoundMenu.generated.h"

/**
 * 
 */
UCLASS()
class EXTRACTIONPROTOCOL_API UBase_SoundMenu : public UUserWidget
{
	GENERATED_BODY()
	
public:

	//Sound menu back button
	UPROPERTY(BlueprintReadWrite, Category = "Button", meta = (BindWidget))
		class UBase_Button* BackButton;

	UPROPERTY(BlueprintReadWrite, Category = "Button", meta = (BindWidget))
		class UBase_Button* VideoButton;

	UPROPERTY(BlueprintReadWrite, Category = "Button", meta = (BindWidget))
		class UBase_Button* ControlsButton;

	UPROPERTY(BlueprintReadWrite, Category = "Button", meta = (BindWidget))
		class UBase_Button* SaveSettingsButton;

	//Sliders
	UPROPERTY(meta = (BindWidget))
		class USlider* MasterSlider;

	UPROPERTY(meta = (BindWidget))
		class USlider* SFXSlider;

	UPROPERTY(meta = (BindWidget))
		class USlider* MusicSlider;

	//Slider Variables

	//Sound Class
	UPROPERTY(EditAnywhere, Category = "Sound Class")
		class USoundClass* MasterSoundClass;

	UPROPERTY(EditAnywhere, Category = "Sound Class")
		class USoundClass* SFXSoundClass;

	UPROPERTY(EditAnywhere, Category = "Sound Class")
		class USoundClass* MusicSoundClass;

	//Sound Mix
	UPROPERTY(EditAnywhere, Category = "SoundMix")
		class USoundMix* MasterSoundMix;

	UPROPERTY(EditAnywhere, Category = "SoundMix")
		class USoundMix* SFXSoundMix;

	UPROPERTY(EditAnywhere, Category = "SoundMix")
		class USoundMix* MusicSoundMix;

	//Text (Info)
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* MasterVolumeText;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* SFXVolumeText;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* MusicVolumeText;

	UPROPERTY(EditAnywhere)
		float Master;

	UPROPERTY()
		float SFX;

	UPROPERTY()
		float Music;

	//Main Menu 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Menu")
		TSubclassOf<class UBase_MainMenu> MainMenuClass;

	UPROPERTY(BlueprintReadWrite, Category = "Menu")
		class UBase_MainMenu* MainWidgetMenu;

	//Video Menu 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Menu")
		TSubclassOf<class UBase_VideoMenu> VideoMenuClass;

	UPROPERTY(BlueprintReadWrite, Category = "Menu")
		class UBase_VideoMenu* VideoWidgetMenu;

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

public:

	virtual void NativeConstruct() override;

	UFUNCTION()
		void OnVideoButtonClicked();

	UFUNCTION()
		void OnControlsButtonClicked();

	UFUNCTION()
		void OnBackButtonClicked();

	UFUNCTION()
		void OnSaveSettingsButtonClicked();

	UFUNCTION()
		void SavedButtonClicked();

	UFUNCTION()
		void OnMasterVolumeChanged(float MasterVolume);

	UFUNCTION()
		void MasterGetText(float Number);

	UFUNCTION()
		void SFXGetText(float Number);

	UFUNCTION()
		void MusicGetText(float Number);

	UFUNCTION()
		void OnSFXVolumeChanged(float SFXVolume);

	UFUNCTION()
		void OnMusicVolumeChanged(float MusicVolume);
};
