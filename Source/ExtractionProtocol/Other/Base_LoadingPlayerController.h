// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Base_LoadingPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class EXTRACTIONPROTOCOL_API ABase_LoadingPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Menu")
        TSubclassOf<class UBase_LoadingScreen> LoadingMenuClass;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Menu")
        class UBase_LoadingScreen* LoadingWidgetMenu;

    ////Level Music
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Menu")
        class USoundBase* MenuMusic;

protected:

    virtual void BeginPlay();

};
