// Fill out your copyright notice in the Description page of Project Settings.


#include "Base_GameInstance.h"
#include "Base_SaveGame.h"
#include "../UI/Base_SoundMenu.h"
#include "../ExtractionProtocol.h"
//Unreal Classes
#include "Kismet/GameplayStatics.h"

UBase_GameInstance::UBase_GameInstance()
{
    FirstLevelIndex = 1;
    Load_Blockout_Level = "Blockout_Level";
}

void UBase_GameInstance::Init()
{
    Super::Init();

    //Load save game file on initialization
    LoadGame();
}

void UBase_GameInstance::CreateSaveFile()
{
    //Create a SaveGame Object and sace to teh default slot
    UBase_SaveGame* DataToSave = Cast<UBase_SaveGame>(UGameplayStatics::CreateSaveGameObject(UBase_SaveGame::StaticClass()));
    UGameplayStatics::SaveGameToSlot(DataToSave, "Slot1", 0);
    UE_LOG(LogTemp, Warning, TEXT("Save Game File Created"));
}

void UBase_GameInstance::SaveGame()
{
    //Initialize data to save
    UBase_SaveGame* DataToSave = Cast<UBase_SaveGame>(UGameplayStatics::LoadGameFromSlot("Slot1", 0));

    //Adds data to Save Variable and save to slot
    if (DataToSave != nullptr)
    {
        //Sound
        DataToSave->MasterVolumeSave = MasterVolumeInstance;
        DataToSave->SFXVolumeSave = SFXVolumeInstance;
        DataToSave->MusicVolumeSave = MusicVolumeInstance;
        //Video
        DataToSave->FullscreenSave = FullscreenInstance;
        DataToSave->WindowedSave = WindowedInstance;
        DataToSave->ResolutionSave = ResolutionInstance;
        DataToSave->FrameRateSave = FrameRateInstance;

        UGameplayStatics::SaveGameToSlot(DataToSave, "Slot1", 0);
    }
    else if (!UGameplayStatics::DoesSaveGameExist("Slot1", 0))
    {
        //Create default save file
        CreateSaveFile();
    }
}

void UBase_GameInstance::LoadGame()
{
    //Retreive data to load
    UBase_SaveGame* DataToLoad = Cast<UBase_SaveGame>(UGameplayStatics::LoadGameFromSlot("Slot1", 0));

    //Loads data into instance variables
    if (DataToLoad != nullptr)
    {
        //Sound
        MasterVolumeInstance = DataToLoad->MasterVolumeSave;
        SFXVolumeInstance = DataToLoad->SFXVolumeSave;
        MusicVolumeInstance = DataToLoad->MusicVolumeSave;

        //Video
        FullscreenInstance = DataToLoad->FullscreenSave;
        WindowedInstance = DataToLoad->WindowedSave;
        ResolutionInstance = DataToLoad->ResolutionSave;
        FrameRateInstance = DataToLoad->FrameRateSave;
    }
    else if (!UGameplayStatics::DoesSaveGameExist("Slot1", 0))
    {
        //Create default save file
        CreateSaveFile();
        
    }
}

void UBase_GameInstance::LoadFirstLevel()
{
    //LoadLevelSafe(FirstLevelIndex);
   UGameplayStatics::OpenLevel(GetWorld(), Load_Blockout_Level);

    FLatentActionInfo info;

   /* UGameplayStatics::LoadStreamLevel(GetWorld(), Load_Blockout_Level, true, false, info);
    UE_LOG(Game, Error, TEXT("Load First Level"));*/
}

void UBase_GameInstance::LoadLevelSafe(int Index)
{
    if (Levels[Index].IsValid())
    {
        CurrentLevel = Index;
        UGameplayStatics::OpenLevel(GetWorld(), Levels[Index]);
    }

    
    
}

void UBase_GameInstance::ReloadLevel()
{
    LoadLevelSafe(CurrentLevel);
}

void UBase_GameInstance::LoadLoadingScreen()
{
    //LoadLevelSafe(2);
    UGameplayStatics::OpenLevel(GetWorld(), Loading_Level);
}

void UBase_GameInstance::QuitGame()
{
    UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, false);
}

void UBase_GameInstance::LoadMainMenu()
{
    LoadLevelSafe(0);
}