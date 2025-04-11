// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Base_SaveGame.generated.h"

/**
 * 
 */
UCLASS()
class EXTRACTIONPROTOCOL_API UBase_SaveGame : public USaveGame
{
	GENERATED_BODY()

public:

	UBase_SaveGame();

	//Sound
	UPROPERTY()
		float MasterVolumeSave;

	UPROPERTY()
		float SFXVolumeSave;

	UPROPERTY()
		float MusicVolumeSave;

	//Video
	UPROPERTY()
		bool FullscreenSave;

	UPROPERTY()
		bool WindowedSave;

	UPROPERTY()
		FIntPoint ResolutionSave;

	UPROPERTY()
		float FrameRateSave;
	
};
