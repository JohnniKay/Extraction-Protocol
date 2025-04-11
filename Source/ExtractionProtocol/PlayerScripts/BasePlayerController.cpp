// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePlayerController.h"
#include "../UI/Base_HUD.h"


//void ABasePlayerController::BeginPlay()
//{
//	if (IsValid(HUDClass))
//	{
//		HUD = CreateWidget<UBase_HUD>(GetLocalPlayer()->GetPlayerController(GetWorld()), HUDClass);
//	}
//
//	if (HUD)
//	{
//		HUD->AddToViewport();
//	}	
//}
//
//void ABasePlayerController::SetHealth(float CurrentHealth, float MaxHealth)
//{
//	HUD->SetHealth(CurrentHealth, MaxHealth);
//}
//
//void ABasePlayerController::SetAmmo(float CurrentAmmo, float CurrentMaxReserve)
//{
//	HUD->SetAmmo(CurrentAmmo, CurrentMaxReserve);
//}