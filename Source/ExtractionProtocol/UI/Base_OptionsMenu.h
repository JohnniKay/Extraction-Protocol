// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Other/Delegates.h"
#include "Blueprint/UserWidget.h"
#include "Base_OptionsMenu.generated.h"

/**
 * 
 */
UCLASS()
class EXTRACTIONPROTOCOL_API UBase_OptionsMenu : public UUserWidget
{
	GENERATED_BODY()

public:

    //Options Buttons
    UPROPERTY(BlueprintReadWrite, Category = "Button", meta = (BindWidget))
        class UBase_Button* VideoButton;

    UPROPERTY(BlueprintReadWrite, Category = "Button", meta = (BindWidget))
        class UBase_Button* SoundButton;

    UPROPERTY(BlueprintReadWrite, Category = "Button", meta = (BindWidget))
        class UBase_Button* ControlsButton;

    //Widget Switcher
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Menu", meta = (BindWidget))
        class UWidgetSwitcher* OptionsSwitcher;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Menu")
        class UBase_VideoMenu* VideoWidgetMenu;

    

public:

    virtual void NativeConstruct() override;

    //Options Menu
    UFUNCTION()
        void OnVideoButtonClicked();

    UFUNCTION()
        void OnSoundButtonClicked();

    UFUNCTION()
        void OnControlsButtonClicked();

};
