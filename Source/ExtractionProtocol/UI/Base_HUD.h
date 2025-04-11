// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Base_HUD.generated.h"

/**
 * 
 */
UCLASS()
class EXTRACTIONPROTOCOL_API UBase_HUD : public UUserWidget
{
	GENERATED_BODY()
	
				
public:
	virtual void NativeConstruct();
	virtual void Tick(float DeltaTime);
	


#pragma region UI Elements
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Compass", meta = (BindWidget))
		class UImage* Compass;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Health", meta = (BindWidget))
		class UProgressBar* HealthBar;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Health", meta = (BindWidget))
		class UTextBlock* CurrentHP;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Health", meta = (BindWidget))
		class UTextBlock* MaxHP;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Ammo", meta = (BindWidget))
		class UTextBlock* CurrentAmmoCount;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Ammo", meta = (BindWidget))
		class UTextBlock* AmmoReserve;

	UFUNCTION()
		void SetHealth(float CurrentHealth, float MaxHealth);
	UFUNCTION()
		void SetAmmo(float CurrentAmmo, float CurrentMaxReserve);

	void SetDirection();
protected:
	// protected UPROPERTY
	// protected FUNCTIONS
private:
	// private UPROPERTY
	// private FUNCTIONS
#pragma endregion
};
