// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Base_GameInstance.generated.h"

/**
 * 
 */
UCLASS()
class EXTRACTIONPROTOCOL_API UBase_GameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:

    UBase_GameInstance();

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Animation");
    TArray<FName> Levels;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Death")
        int FirstLevelIndex;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
        int CurrentLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Menu")
    FName Load_Blockout_Level;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Menu")
        FName Loading_Level;

    //Sound
    UPROPERTY()
        float MasterVolumeInstance;

    UPROPERTY()
        float SFXVolumeInstance;

    UPROPERTY()
        float MusicVolumeInstance;

    //Video
    //UPROPERTY()
     //	 ScreenSizeInstance;

    UPROPERTY()
        FIntPoint ResolutionInstance;

    UPROPERTY()
        float FrameRateInstance;

    UPROPERTY()
        bool FullscreenInstance;

    UPROPERTY()
        bool WindowedInstance;

public:

    UFUNCTION()
        virtual void Init() override;

    UFUNCTION()
        void CreateSaveFile();

    UFUNCTION()
        void SaveGame();

    UFUNCTION()
        void LoadGame();

    UFUNCTION()
        void LoadFirstLevel();

    UFUNCTION()
        void LoadMainMenu();

    UFUNCTION()
        void ReloadLevel();

    UFUNCTION()
        void LoadLoadingScreen();

    UFUNCTION()
        void QuitGame();

private:

    UFUNCTION()
        void LoadLevelSafe(int Index);
};
