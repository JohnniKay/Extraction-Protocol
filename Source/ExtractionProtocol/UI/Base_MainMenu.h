// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Base_MainMenu.generated.h"

/**
 * 
 */
UCLASS()
class EXTRACTIONPROTOCOL_API UBase_MainMenu : public UUserWidget
{
	GENERATED_BODY()
	
public:
    //Main Menu Buttons
    UPROPERTY(BlueprintReadWrite, Category = "Button", meta = (BindWidget))
        class UBase_Button* StartButton;

    UPROPERTY(BlueprintReadWrite, Category = "Button", meta = (BindWidget))
       class UBase_Button* OptionsButton;

    UPROPERTY(BlueprintReadWrite, Category = "Button", meta = (BindWidget))
        class UBase_Button* CreditsButton;

    UPROPERTY(BlueprintReadWrite, Category = "Button", meta = (BindWidget))
        class UBase_Button* QuitButton;


    //GameInstance
    UPROPERTY(BlueprintReadWrite, Category = "Game Instance")
        class UBase_GameInstance* GameInstance;

    //Co-op Menu
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Menu")
        TSubclassOf<class UBase_CoopMenu> CoopMenuClass;

    UPROPERTY(BlueprintReadWrite)
        class UBase_CoopMenu* CoopWidgetMenu;

    ////Credits Menu 
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Menu")
        TSubclassOf<class UBase_CreditsMenu> CreditsMenuClass;

    UPROPERTY(BlueprintReadWrite, Category = "Menu")
        class UBase_CreditsMenu* CreditsWidgetMenu;

    //Video Menu which would be the options button
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Menu")
        TSubclassOf<class UBase_VideoMenu> VideoMenuClass;

    UPROPERTY(BlueprintReadWrite, Category = "Menu")
        class UBase_VideoMenu* VideoWidgetMenu;

    //Sound Menu
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Menu")
        TSubclassOf<class UBase_SoundMenu> SoundMenuClass;

    UPROPERTY(BlueprintReadWrite, Category = "Menu")
        class UBase_SoundMenu* SoundWidgetMenu;

    float Time;

    UPROPERTY(EditAnywhere)
        float Master;

    UPROPERTY()
        float SFX;

    UPROPERTY()
        float Music;

    //Sound Class
    UPROPERTY(EditAnywhere, Category = "Sound Class")
        class USoundClass* MasterSoundClass;

    UPROPERTY(EditAnywhere, Category = "Sound Class")
        class USoundClass* SFXSoundClass;

    UPROPERTY(EditAnywhere, Category = "Sound Class")
        class USoundClass* MusicSoundClass;

    //Sound Mix
    UPROPERTY(EditAnywhere, Category = "SoundMix")
        class USoundMix* MasterSoundMix;

    UPROPERTY(EditAnywhere, Category = "SoundMix")
        class USoundMix* SFXSoundMix;

    UPROPERTY(EditAnywhere, Category = "SoundMix")
        class USoundMix* MusicSoundMix;

    //Video variables
    UPROPERTY()
        bool Fullscreen;

    UPROPERTY()
        bool Windowed;

    UPROPERTY()
        FIntPoint Resolution;

    UPROPERTY()
        float FrameRate;

public:

    virtual void NativePreConstruct() override;

    virtual void NativeConstruct() override;

    //Main Menu Clicked
    UFUNCTION()
        void OnStartButtonClicked();

    UFUNCTION()
        void OnMainOptionsButtonClicked();

    UFUNCTION()
        void OnCreditsButtonClicked();

    UFUNCTION()
        void OnQuitButtonClicked();

    UFUNCTION()
        void LoadSettings();


};
