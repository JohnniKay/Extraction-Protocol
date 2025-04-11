// Fill out your copyright notice in the Description page of Project Settings.

//Created Classes
#include "Base_GameOverMenu.h"
#include "Base_Button.h"
#include "Base_MainMenu.h"
#include "../ExtractionProtocol.h"
#include "../Other/Base_GameInstance.h"

void UBase_GameOverMenu::NativePreConstruct()
{
    Super::NativePreConstruct();

    GameInstance = Cast<UBase_GameInstance>(GetGameInstance());
    if (GameInstance != nullptr)
    {
        UE_LOG(Game, Warning, TEXT("Good GameInstance"));
    }
    else
    {
        UE_LOG(Game, Error, TEXT("Bad GameInstance Main Menu"));
    }
}

void UBase_GameOverMenu::NativeConstruct()
{
    Super::NativeConstruct();

	PlayAgainButton->OnButtonClicked.AddDynamic(this, &UBase_GameOverMenu::OnPlayAgainButtonClicked);
	MainMenuButton->OnButtonClicked.AddDynamic(this, &UBase_GameOverMenu::OnMainMenuButtonClicked);
}

void UBase_GameOverMenu::OnPlayAgainButtonClicked()
{
    GameInstance->LoadFirstLevel();
}

void UBase_GameOverMenu::OnMainMenuButtonClicked()
{

    GameInstance->LoadMainMenu();
   /* if (IsValid(MenuClass))
    {
        WidgetMenu = CreateWidget<UBase_MainMenu>(this, MenuClass);
    }
    if (WidgetMenu != nullptr)
    {
        WidgetMenu->AddToViewport();
        RemoveFromParent();
    }
    else
    {
        UE_LOG(Game, Error, TEXT("MainWidgetMenu is Invalid "));
    }*/
}
