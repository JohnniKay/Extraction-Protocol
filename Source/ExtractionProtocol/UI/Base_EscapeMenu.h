// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Base_EscapeMenu.generated.h"

/**
 * 
 */
UCLASS()
class EXTRACTIONPROTOCOL_API UBase_EscapeMenu : public UUserWidget
{
	GENERATED_BODY()

public:
    // Menu Buttons
    UPROPERTY(BlueprintReadWrite, Category = "Button", meta = (BindWidget))
        class UBase_Button* OptionsButton;

    UPROPERTY(BlueprintReadWrite, Category = "Button", meta = (BindWidget))
        class UBase_Button* LeaveButton;

    //GameInstance
    UPROPERTY(BlueprintReadWrite, Category = "Game Instance")
        class UBase_GameInstance* GameInstance;

    //Options Menu
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Menu")
        TSubclassOf<class UBase_OptionsMenu> OptionsMenuClass;

    UPROPERTY(BlueprintReadWrite)
        class UBase_OptionsMenu* OptionsWidgetMenu;

    //Main Menu
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Menu")
        TSubclassOf<class UBase_MainMenu> MainMenuClass;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Menu")
        class UBase_MainMenu* MainWidgetMenu;
	
public:

    virtual void NativePreConstruct() override;

    virtual void NativeConstruct() override;

    //Escape Menu
    UFUNCTION()
        void OnEscapeOptionsButtonClicked();

    UFUNCTION()
        void OnQuitButtonClicked();

};
