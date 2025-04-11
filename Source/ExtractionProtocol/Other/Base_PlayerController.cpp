// Fill out your copyright notice in the Description page of Project Settings.


#include "Base_PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetBlueprintLibrary.h"


#include "../UI/Base_CharacterHUD.h"
#include "../UI/Base_HUD.h"

void ABase_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	UWidgetBlueprintLibrary::SetInputMode_GameOnly(this);
	UGameplayStatics::PlaySound2D(GetWorld(), MenuMusic, 0.05);

	CharacterHUD = Cast<ABase_CharacterHUD>(GetHUD());
}

void ABase_PlayerController::SetHealth(float CurrentHealth, float MaxHealth)
{
	CharacterHUD = CharacterHUD == nullptr ? Cast<ABase_CharacterHUD>(GetHUD()) : CharacterHUD;

	if (CharacterHUD && CharacterHUD->HUD)
	{
		CharacterHUD->HUD->SetHealth(CurrentHealth, MaxHealth);		
	}
}

void ABase_PlayerController::SetAmmo(float CurrentAmmo, float CurrentMaxReserve)
{
	CharacterHUD = CharacterHUD == nullptr ? Cast<ABase_CharacterHUD>(GetHUD()) : CharacterHUD;

	if (CharacterHUD && CharacterHUD->HUD)
	{
		CharacterHUD->HUD->SetAmmo(CurrentAmmo, CurrentMaxReserve);
	}
}
