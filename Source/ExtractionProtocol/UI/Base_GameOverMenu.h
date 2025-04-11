// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Base_GameOverMenu.generated.h"

/**
 * 
 */
UCLASS()
class EXTRACTIONPROTOCOL_API UBase_GameOverMenu : public UUserWidget
{
	GENERATED_BODY()

public:

    //Gameover Buttons
    UPROPERTY(BlueprintReadWrite, Category = "Button", meta = (BindWidget))
        class UBase_Button* PlayAgainButton;

    UPROPERTY(BlueprintReadWrite, Category = "Button", meta = (BindWidget))
        class UBase_Button* MainMenuButton;

    UPROPERTY(BlueprintReadWrite, Category = "Menu")
        class UBase_GameInstance* GameInstance;
    //Main Menu
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Menu")
        TSubclassOf<class UBase_MainMenu> MenuClass;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Menu")
        class UBase_MainMenu* WidgetMenu;

public:

    virtual void NativePreConstruct() override;

    virtual void NativeConstruct() override;

    //Options Menu
    UFUNCTION()
        void OnPlayAgainButtonClicked();

    UFUNCTION()
        void OnMainMenuButtonClicked();
	
};
