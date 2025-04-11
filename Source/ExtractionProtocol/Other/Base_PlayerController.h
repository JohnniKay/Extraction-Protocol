// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Base_PlayerController.generated.h"

/**
 * 
 */
UCLASS()
class EXTRACTIONPROTOCOL_API ABase_PlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

	// Button Clicked sound
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Menu")
		class USoundBase* MenuMusic;


#pragma region HUD Functions
public:	
	UFUNCTION()
		void SetHealth(float CurrentHealth, float MaxHealth);
	UFUNCTION()
		void SetAmmo(float CurrentAmmo, float CurrentMaxReserve);
protected:
	// protected UPROPERTY
	// protected FUNCTIONS
private:
	class ABase_CharacterHUD* CharacterHUD;
#pragma endregion
};
