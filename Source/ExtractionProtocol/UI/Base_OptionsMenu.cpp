// Fill out your copyright notice in the Description page of Project Settings.


#include "Base_OptionsMenu.h"
#include "Base_MainMenu.h"
#include "Base_VideoMenu.h"
#include "Base_Button.h"
#include "../ExtractionProtocol.h"
//Unreal Classes
#include "Components/WidgetSwitcher.h"

void UBase_OptionsMenu::NativeConstruct()
{
    VideoButton->OnButtonClicked.AddDynamic(this, &UBase_OptionsMenu::OnVideoButtonClicked);
    SoundButton->OnButtonClicked.AddDynamic(this, &UBase_OptionsMenu::OnSoundButtonClicked);
    ControlsButton->OnButtonClicked.AddDynamic(this, &UBase_OptionsMenu::OnControlsButtonClicked);
}

void UBase_OptionsMenu::OnVideoButtonClicked()
{
   OptionsSwitcher->UWidgetSwitcher::SetActiveWidgetIndex(0);
}

void UBase_OptionsMenu::OnSoundButtonClicked()
{
   OptionsSwitcher->UWidgetSwitcher::SetActiveWidgetIndex(1);
}

void UBase_OptionsMenu::OnControlsButtonClicked()
{
   OptionsSwitcher->UWidgetSwitcher::SetActiveWidgetIndex(2);
}
