// Fill out your copyright notice in the Description page of Project Settings.

//Created Classes
#include "Base_CreditsMenu.h"
#include "Base_Button.h"
#include "Base_MainMenu.h"
#include "../ExtractionProtocol.h"
//Unreal Classes
#include "Animation/WidgetAnimation.h"


void UBase_CreditsMenu::NativeConstruct()
{
	BackButton->OnButtonClicked.AddDynamic(this, &UBase_CreditsMenu::OnBackButtonClicked);
	PlayAnimation(ScrollAnimation, 0.0f, 1, EUMGSequencePlayMode::Forward, 1.0f, false);
}

void UBase_CreditsMenu::OnBackButtonClicked()
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
		UE_LOG(Game, Error, TEXT("MainWidgetMenu is Invalid "));
	}
}

