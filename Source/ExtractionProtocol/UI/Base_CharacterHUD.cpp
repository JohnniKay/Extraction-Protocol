// Fill out your copyright notice in the Description page of Project Settings.


#include "Base_CharacterHUD.h"
#include "../UI/Base_HUD.h"

void ABase_CharacterHUD::BeginPlay()
{
	Super::BeginPlay();

	AddHUD();	
}	

void ABase_CharacterHUD::AddHUD()
{
	APlayerController* PlayerController = GetOwningPlayerController();

	if (PlayerController && HUDClass)
	{
		HUD = CreateWidget<UBase_HUD>(PlayerController, HUDClass);
		HUD->AddToViewport();
	}
}