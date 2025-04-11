// Fill out your copyright notice in the Description page of Project Settings.

//Created Classes
#include "Base_MainMenu.h"
#include "Base_Button.h"
#include "Base_CoopMenu.h"
#include "Base_VideoMenu.h"
#include "Base_SoundMenu.h"
#include "Base_CreditsMenu.h"
#include "../ExtractionProtocol.h"
#include "../Other/Base_GameInstance.h"
//Unreal Classes
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "GameFramework/GameUserSettings.h"
#include "Components/WidgetSwitcher.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Slider.h"


void UBase_MainMenu::NativePreConstruct()
{
    GameInstance = Cast<UBase_GameInstance>(GetGameInstance());
    if (GameInstance != nullptr)
    {
        UE_LOG(Game, Warning, TEXT("Good GameInstance"));
    }
    else
    {
        UE_LOG(Game, Error, TEXT("Bad GameInstance Main Menu"));
    }

    Time = 0.3f;
}

void UBase_MainMenu::NativeConstruct()
{
    //Creates Video Menu
    if (IsValid(VideoMenuClass))
    {
        VideoWidgetMenu = CreateWidget<UBase_VideoMenu>(this, VideoMenuClass);
        VideoWidgetMenu->LoadSettings();
    }

    //Main Menu Clicked
    StartButton->OnButtonClicked.AddDynamic(this, &UBase_MainMenu::OnStartButtonClicked);
    OptionsButton->OnButtonClicked.AddDynamic(this, &UBase_MainMenu::OnMainOptionsButtonClicked);
    CreditsButton->OnButtonClicked.AddDynamic(this, &UBase_MainMenu::OnCreditsButtonClicked);
    QuitButton->OnButtonClicked.AddDynamic(this, &UBase_MainMenu::OnQuitButtonClicked);

    LoadSettings();

}

void UBase_MainMenu::OnStartButtonClicked()
{
    //Creates Co-op Menu
    if (IsValid(CoopMenuClass))
    {
        CoopWidgetMenu = CreateWidget<UBase_CoopMenu>(this, CoopMenuClass);
    }
    if (CoopWidgetMenu != nullptr)
    {
        CoopWidgetMenu->MenuSetup(2, "Default", "/Game/Core/Maps/Blockout_Level"); // - Kyle
        CoopWidgetMenu->AddToViewport();
        RemoveFromParent(); // Potential Error here - Kyle
    }
    else
    {
        UE_LOG(Game, Error, TEXT("CoopMainWidgetMenu is Invalid (Main) "));
    }
}

void UBase_MainMenu::OnMainOptionsButtonClicked()
{//Creates Video Menu
    if (IsValid(VideoMenuClass))
    {
        VideoWidgetMenu = CreateWidget<UBase_VideoMenu>(this, VideoMenuClass);
    }
    if (VideoWidgetMenu != nullptr)
    {
        VideoWidgetMenu->AddToViewport();
        RemoveFromParent();
    }
    else
    {
        UE_LOG(Game, Error, TEXT("VideoWidgetMenu is Invalid (Main)"));
    }
}

void UBase_MainMenu::OnCreditsButtonClicked()
{
    if (IsValid(CreditsMenuClass))
    {
        CreditsWidgetMenu = CreateWidget<UBase_CreditsMenu>(this, CreditsMenuClass);
    }
    if (CreditsWidgetMenu != nullptr)
    {
        CreditsWidgetMenu->AddToViewport();
        RemoveFromParent();
    }
    else
    {
        UE_LOG(Game, Error, TEXT("MainWidgetMenu is Invalid (Main)"));
    }
}

void UBase_MainMenu::OnQuitButtonClicked()
{
    FTimerHandle Timer;
    GetWorld()->GetTimerManager().SetTimer(Timer, GameInstance, &UBase_GameInstance::QuitGame, Time);
}

void UBase_MainMenu::LoadSettings()
{
    //Sound
    Master = GameInstance->MasterVolumeInstance;
    SFX = GameInstance->SFXVolumeInstance;
    Music = GameInstance->MusicVolumeInstance;

    UGameplayStatics::SetSoundMixClassOverride(GetWorld(), MasterSoundMix, MasterSoundClass, Master, 1.0f, 0.f, true);
    UGameplayStatics::PushSoundMixModifier(GetWorld(), MasterSoundMix);

    UGameplayStatics::SetSoundMixClassOverride(GetWorld(), SFXSoundMix, SFXSoundClass, SFX, 1.0f, 0.f, true);
    UGameplayStatics::PushSoundMixModifier(GetWorld(), SFXSoundMix);

    UGameplayStatics::SetSoundMixClassOverride(GetWorld(), MusicSoundMix, MusicSoundClass, Music, 1.0f, 0.f, true);
    UGameplayStatics::PushSoundMixModifier(GetWorld(), MusicSoundMix);

    //Video
    Fullscreen = GameInstance->FullscreenInstance;
    Windowed = GameInstance->WindowedInstance;
    Resolution = GameInstance->ResolutionInstance;
    FrameRate = GameInstance->FrameRateInstance;

    if (Fullscreen == true)
    {
        UGameUserSettings::GetGameUserSettings()->UGameUserSettings::SetFullscreenMode(EWindowMode::Fullscreen);
    }
    else if (Windowed == true)
    {
        UGameUserSettings::GetGameUserSettings()->UGameUserSettings::SetFullscreenMode(EWindowMode::Windowed);
    }

    UGameUserSettings::GetGameUserSettings()->UGameUserSettings::SetScreenResolution(Resolution);
    UGameUserSettings::GetGameUserSettings()->UGameUserSettings::SetFrameRateLimit(FrameRate);
}
