// Fill out your copyright notice in the Description page of Project Settings.

//Created Classes
#include "Base_MenuController.h"
#include "../UI/Base_MainMenu.h"
#include "../ExtractionProtocol.h"
//Unreal Classes
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

void ABase_MenuController::BeginPlay()
{
    Super::BeginPlay();

    if (IsValid(MenuClass))
    {
        WidgetMenu = CreateWidget<UBase_MainMenu>(this, MenuClass);
    }
    if (WidgetMenu != nullptr)
    {
        WidgetMenu->AddToViewport();
        UGameplayStatics::PlaySound2D(GetWorld(), MenuMusic, 5.f);
    }
    else
    {
        UE_LOG(Game, Error, TEXT("MainWidgetMenu is Invalid "));
    }
    
    UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(this, WidgetMenu, EMouseLockMode::LockAlways);
}