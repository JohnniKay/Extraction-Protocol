// Fill out your copyright notice in the Description page of Project Settings.

//Created Classes
#include "Base_HUD.h"
#include "../PlayerScripts/BaseCharacter.h"
//Unreal Classes
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Progressbar.h"
#include "Kismet/KismetTextLibrary.h"

void UBase_HUD::NativeConstruct()
{
	////Rotation->
	//ABaseCharacter* Character;
	////Character->Camera->GetWorld
	//Character->Camera->Rotation = Cast<ABaseCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	
	
}

void UBase_HUD::Tick(float DeltaTime)
{
	//Compass->SetScaler
	//UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetControlRotation().Yaw / 360;
}

void UBase_HUD::SetHealth(float CurrentHealth, float MaxHealth)
{
	if (MaxHealth != 0.f)
	{
		if (IsValid(HealthBar) && IsValid(CurrentHP) && IsValid(MaxHP))
		{
			HealthBar->SetPercent(CurrentHealth / MaxHealth);

			CurrentHP->UTextBlock::SetText(UKismetTextLibrary::Conv_FloatToText(CurrentHealth, ERoundingMode::HalfToEven, false, true));
			MaxHP->UTextBlock::SetText(UKismetTextLibrary::Conv_FloatToText(MaxHealth, ERoundingMode::HalfToEven, false, true));
		}
	}
}

void UBase_HUD::SetAmmo(float CurrentAmmo, float CurrentMaxReserve)
{
	if (IsValid(CurrentAmmoCount) && IsValid(AmmoReserve))
	{		
		CurrentAmmoCount->UTextBlock::SetText(UKismetTextLibrary::Conv_FloatToText(CurrentAmmo, ERoundingMode::HalfToEven, false, true));
		AmmoReserve->UTextBlock::SetText(UKismetTextLibrary::Conv_FloatToText(CurrentMaxReserve, ERoundingMode::HalfToEven, false, true));
	}
}

void UBase_HUD::SetDirection()
{
	
}
