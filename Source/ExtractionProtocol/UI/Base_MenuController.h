// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Base_MenuController.generated.h"

/**
 * 
 */
UCLASS()
class EXTRACTIONPROTOCOL_API ABase_MenuController : public APlayerController
{
	GENERATED_BODY()
	
public:

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Menu")
        TSubclassOf<class UBase_MainMenu> MenuClass;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Menu")
        class UBase_MainMenu* WidgetMenu;

    ////Button Clicked sound
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Menu")
        class USoundBase* MenuMusic;

protected:

    virtual void BeginPlay();
};
