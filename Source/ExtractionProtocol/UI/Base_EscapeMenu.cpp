// Fill out your copyright notice in the Description page of Project Settings.

//Created Classes
#include "Base_EscapeMenu.h"
#include "Base_Button.h"
#include "Base_MainMenu.h"
#include "Base_OptionsMenu.h"
#include "../ExtractionProtocol.h"
#include "../Other/Base_GameInstance.h"

void UBase_EscapeMenu::NativePreConstruct()
{
    GameInstance = Cast<UBase_GameInstance>(GetGameInstance());
    if (GameInstance != nullptr)
    {
        UE_LOG(Game, Warning, TEXT("Good Escape GameInstance"));
    }
    else
    {
        UE_LOG(Game, Error, TEXT("Bad Escape GameInstance Main Menu"));
    }
}

void UBase_EscapeMenu::NativeConstruct()
{
    OptionsButton->OnButtonClicked.AddDynamic(this, &UBase_EscapeMenu::OnEscapeOptionsButtonClicked);
    LeaveButton->OnButtonClicked.AddDynamic(this, &UBase_EscapeMenu::OnQuitButtonClicked);
}

void UBase_EscapeMenu::OnEscapeOptionsButtonClicked()
{
    //Creates Options Menu
    if (IsValid(OptionsMenuClass))
    {
        OptionsWidgetMenu = CreateWidget<UBase_OptionsMenu>(this, OptionsMenuClass);
    }
    if (OptionsWidgetMenu != nullptr)
    {
        OptionsWidgetMenu->AddToViewport();
        RemoveFromParent();
    }
    else
    {
        UE_LOG(Game, Error, TEXT("EscapeOptionsWidgetMenu is Invalid "));
    }
}

void UBase_EscapeMenu::OnQuitButtonClicked()
{
    GameInstance->UBase_GameInstance::QuitGame();
}