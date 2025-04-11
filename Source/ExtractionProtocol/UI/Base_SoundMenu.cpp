// Fill out your copyright notice in the Description page of Project Settings.

//Created Classes
#include "Base_SoundMenu.h"
#include "Base_Button.h"
#include "Base_MainMenu.h"
#include "Base_VideoMenu.h"
#include "Base_ControlsMenu.h"
#include "../ExtractionProtocol.h"
#include "../Other/Base_GameInstance.h"
//Unreal Classes
#include "Sound/SoundBase.h"
#include "Components/Slider.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetTextLibrary.h"
#include "GameFramework/GameUserSettings.h"

void UBase_SoundMenu::NativeConstruct()
{
	//Sound Menu CLicked
	VideoButton->OnButtonClicked.AddDynamic(this, &UBase_SoundMenu::OnVideoButtonClicked);
	ControlsButton->OnButtonClicked.AddDynamic(this, &UBase_SoundMenu::OnControlsButtonClicked);
	BackButton->OnButtonClicked.AddDynamic(this, &UBase_SoundMenu::OnBackButtonClicked);
	SaveSettingsButton->OnButtonClicked.AddDynamic(this, &UBase_SoundMenu::OnSaveSettingsButtonClicked);

	//Sliders
	MasterSlider->OnValueChanged.AddDynamic(this, &UBase_SoundMenu::OnMasterVolumeChanged);
	SFXSlider->OnValueChanged.AddDynamic(this, &UBase_SoundMenu::OnSFXVolumeChanged);
	MusicSlider->OnValueChanged.AddDynamic(this, &UBase_SoundMenu::OnMusicVolumeChanged);

	if (auto BaseGameInstance = Cast<UBase_GameInstance>(GetGameInstance()))
	{
		//Set Slider variable from save
		Master = BaseGameInstance->MasterVolumeInstance;
		SFX = BaseGameInstance->SFXVolumeInstance;
		Music = BaseGameInstance->MusicVolumeInstance;
		//Set Slider Value
		MasterSlider->SetValue(Master);
		SFXSlider->SetValue(SFX);
		MusicSlider->SetValue(Music);
		//Set Slider Text
		MasterGetText(Master);
		SFXGetText(SFX);
		MusicGetText(Music);
	}
}

void UBase_SoundMenu::OnVideoButtonClicked()
{//Creates Video Menu
	if (IsValid(VideoMenuClass))
	{
		VideoWidgetMenu = CreateWidget<UBase_VideoMenu>(this, VideoMenuClass);
	}
	if (VideoWidgetMenu != nullptr)
	{
		VideoWidgetMenu->AddToViewport();
		RemoveFromParent();
	}
	else
	{
		UE_LOG(Game, Error, TEXT("VideoWidgetMenu is Invalid (Sound)"));
	}
}

void UBase_SoundMenu::OnControlsButtonClicked()
{
	if (IsValid(ControlsMenuClass))
	{
		ControlsWidgetMenu = CreateWidget<UBase_ControlsMenu>(this, ControlsMenuClass);
	}
	if (ControlsWidgetMenu != nullptr)
	{
		ControlsWidgetMenu->AddToViewport();
		RemoveFromParent();
	}
	else
	{
		UE_LOG(Game, Error, TEXT("ControlsWidgetMenu is Invalid (Sound)"));
	}
}

void UBase_SoundMenu::OnBackButtonClicked()
{
	if (IsValid(MainMenuClass))
	{
		MainWidgetMenu = CreateWidget<UBase_MainMenu>(this, MainMenuClass);
	}
	if (MainWidgetMenu != nullptr)
	{
		MainWidgetMenu->AddToViewport();
		RemoveFromParent();
	}
	else
	{
		UE_LOG(Game, Error, TEXT("MainWidgetMenu is Invalid (Sound)"));
	}
}

void UBase_SoundMenu::OnSaveSettingsButtonClicked()
{
	/*if (IsValid(SaveSettingsMenuClass))
	{
		SaveSettingsWidgetMenu = CreateWidget<UBase_ConfirmationMenu>(this, SaveSettingsMenuClass);
	}
	if (SaveSettingsWidgetMenu != nullptr)
	{
		SaveSettingsWidgetMenu->AddToViewport();
	}
	else
	{
		UE_LOG(MyLog, Error, TEXT("MainWidgetMenu is Invalid (Sound) "));
	}	*/

	if (auto BaseGameInstance = Cast<UBase_GameInstance>(GetGameInstance()))
	{
		UE_LOG(Game, Error, TEXT("SavedButtonClicked"));
		BaseGameInstance->MasterVolumeInstance = Master;
		BaseGameInstance->SFXVolumeInstance = SFX;
		BaseGameInstance->MusicVolumeInstance = Music;
		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Blue, FString::Printf(TEXT("SoundMenu: Saved")));
		BaseGameInstance->SaveGame();
	}
}

void UBase_SoundMenu::SavedButtonClicked()
{


}

void UBase_SoundMenu::OnMasterVolumeChanged(float MasterVolume)
{
	UE_LOG(Game, Error, TEXT("MasterSound"));
	UGameplayStatics::SetSoundMixClassOverride(GetWorld(), MasterSoundMix, MasterSoundClass, MasterVolume, 1.0f, 0.f, true);
	UGameplayStatics::PushSoundMixModifier(GetWorld(), MasterSoundMix);
	Master = MasterVolume;
	MasterGetText(Master);

}

void UBase_SoundMenu::OnSFXVolumeChanged(float SFXVolume)
{
	UE_LOG(Game, Error, TEXT("SFXSound"));
	UGameplayStatics::SetSoundMixClassOverride(GetWorld(), SFXSoundMix, SFXSoundClass, SFXVolume, 1.0f, 0.f, true);
	UGameplayStatics::PushSoundMixModifier(GetWorld(), SFXSoundMix);
	SFX = SFXVolume;
	SFXGetText(SFX);
}

void UBase_SoundMenu::OnMusicVolumeChanged(float MusicVolume)
{
	UE_LOG(Game, Error, TEXT("MusicSound"));
	UGameplayStatics::SetSoundMixClassOverride(GetWorld(), MusicSoundMix, MusicSoundClass, MusicVolume, 1.0f, 0.f, true);
	UGameplayStatics::PushSoundMixModifier(GetWorld(), MusicSoundMix);
	Music = MusicVolume;
	MusicGetText(Music);
}

void UBase_SoundMenu::MasterGetText(float Number)
{
	float TruncNumber = (Number * 50);;
	int IntText = (int)TruncNumber;
	FText NumText = UKismetTextLibrary::Conv_IntToText(IntText);
	MasterVolumeText->SetText(NumText);;

}

void UBase_SoundMenu::SFXGetText(float Number)
{
	float TruncNumber = (Number * 50);;
	int IntText = (int)TruncNumber;
	FText NumText = UKismetTextLibrary::Conv_IntToText(IntText);
	SFXVolumeText->SetText(NumText);
}

void UBase_SoundMenu::MusicGetText(float Number)
{
	float TruncNumber = (Number * 50);;
	int IntText = (int)TruncNumber;
	FText NumText = UKismetTextLibrary::Conv_IntToText(IntText);
	MusicVolumeText->SetText(NumText);
}