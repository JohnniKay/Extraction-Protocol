// Fill out your copyright notice in the Description page of Project Settings.


#include "Base_LoadingScreen.h"
#include "../ExtractionProtocol.h"
#include "../Other/Base_GameInstance.h"

void UBase_LoadingScreen::NativePreConstruct()
{
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

void UBase_LoadingScreen::NativeConstruct()
{
    GameInstance->UBase_GameInstance::LoadFirstLevel();
}
