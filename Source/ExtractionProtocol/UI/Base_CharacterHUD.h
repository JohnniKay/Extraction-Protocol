// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Base_CharacterHUD.generated.h"

/**
 * 
 */
UCLASS()
class EXTRACTIONPROTOCOL_API ABase_CharacterHUD : public AHUD
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

#pragma region HUD Functions
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Menu")
		TSubclassOf<class UBase_HUD> HUDClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UBase_HUD* HUD;		
protected:
	void AddHUD();
private:
	// private UPROPERTY
	// private FUNCTIONS
#pragma endregion
};
