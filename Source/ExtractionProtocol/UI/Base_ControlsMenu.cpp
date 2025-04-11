// Fill out your copyright notice in the Description page of Project Settings.

//Created Classes
#include "Base_ControlsMenu.h"
#include "Base_Button.h"
#include "Base_VideoMenu.h"
#include "Base_MainMenu.h"
#include "Base_SoundMenu.h"
#include "../ExtractionProtocol.h"
//Engine Classes
#include "GameFramework/GameUserSettings.h"

void UBase_ControlsMenu::NativeConstruct()
{
	//Controls Menu Clicked
	VideoButton->OnButtonClicked.AddDynamic(this, &UBase_ControlsMenu::OnVideoButtonClicked);
	SoundButton->OnButtonClicked.AddDynamic(this, &UBase_ControlsMenu::OnSoundButtonClicked);
	BackButton->OnButtonClicked.AddDynamic(this, &UBase_ControlsMenu::OnBackButtonClicked);
}

void UBase_ControlsMenu::OnVideoButtonClicked()
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
		UE_LOG(Game, Error, TEXT("VideoWidgetMenu is Invalid (Controls)"));
	}
}

void UBase_ControlsMenu::OnSoundButtonClicked()
{//Creates Sound Menu
	if (IsValid(SoundMenuClass))
	{
		SoundWidgetMenu = CreateWidget<UBase_SoundMenu>(this, SoundMenuClass);
	}
	if (SoundWidgetMenu != nullptr)
	{
		SoundWidgetMenu->AddToViewport();
		RemoveFromParent();
	}
	else
	{
		UE_LOG(Game, Error, TEXT("SOundWidgetMenu is Invalid (Controls) "));
	}
}

void UBase_ControlsMenu::OnBackButtonClicked()
{//Creates Main Menu
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
		UE_LOG(Game, Error, TEXT("MainWidgetMenu is Invalid (Controls) "));
	}
}