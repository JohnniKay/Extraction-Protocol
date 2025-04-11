// Fill out your copyright notice in the Description page of Project Settings.


#include "Base_SaveGame.h"
#include "../ExtractionProtocol.h"

UBase_SaveGame::UBase_SaveGame()
{//Set the default values for the variables

	//Sound
	MasterVolumeSave = 1.0f;
	SFXVolumeSave = 1.0f;
	MusicVolumeSave = 1.0f;
	//Video
	FullscreenSave = false;
	WindowedSave = false;
	ResolutionSave = (1280, 720);
	FrameRateSave = 30.f;
}
