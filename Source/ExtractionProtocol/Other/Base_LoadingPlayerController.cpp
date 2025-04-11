// Fill out your copyright notice in the Description page of Project Settings.


#include "Base_LoadingPlayerController.h"
#include "../UI/Base_LoadingScreen.h"
#include "../ExtractionProtocol.h"
//Unreal Classes
#include "Kismet/GameplayStatics.h"

void ABase_LoadingPlayerController::BeginPlay()
{
    Super::BeginPlay();

    if (IsValid(LoadingMenuClass))
    {
        LoadingWidgetMenu = CreateWidget<UBase_LoadingScreen>(this, LoadingMenuClass);
    }
    if (LoadingWidgetMenu != nullptr)
    {
        LoadingWidgetMenu->AddToViewport();
        UGameplayStatics::PlaySound2D(GetWorld(), MenuMusic, 5.f);
    }
    else
    {
        UE_LOG(Game, Error, TEXT("MainWidgetMenu is Invalid "));
    }

    //UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(this, WidgetMenu, EMouseLockMode::LockAlways);
}