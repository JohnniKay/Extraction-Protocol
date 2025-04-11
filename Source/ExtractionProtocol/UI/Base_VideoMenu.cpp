// Fill out your copyright notice in the Description page of Project Settings.

//Created Classes
#include "Base_VideoMenu.h"
#include "Base_MainMenu.h"
#include "Base_SoundMenu.h"
#include "Base_ControlsMenu.h"
#include "Base_Button.h"
//#include "Base_ConfirmationMenu.h"
#include "../ExtractionProtocol.h"
#include "../Other/Base_GameInstance.h"
//Unreal Classes
#include "Kismet/KismetStringLibrary.h"
#include "GameFramework/GameUserSettings.h"

void UBase_VideoMenu::NativePreConstruct()
{
	GameInstance = Cast<UBase_GameInstance>(GetGameInstance());
	if (GameInstance != nullptr)
	{
		UE_LOG(Game, Warning, TEXT("Good GameInstance"));
	}
	else
	{
		UE_LOG(Game, Error, TEXT("Bad GameInstance Video Menu"));
	}
}

void UBase_VideoMenu::NativeConstruct()
{
	//Video Menu Clicked
	SoundButton->OnButtonClicked.AddDynamic(this, &UBase_VideoMenu::OnSoundButtonClicked);
	ControlsButton->OnButtonClicked.AddDynamic(this, &UBase_VideoMenu::OnControlsButtonClicked);
	BackButton->OnButtonClicked.AddDynamic(this, &UBase_VideoMenu::OnBackButtonClicked);
	SaveSettingsButton->OnButtonClicked.AddDynamic(this, &UBase_VideoMenu::OnSaveSettingsButtonClicked);
	//Screen Size
	FullscreenButton->OnButtonClicked.AddDynamic(this, &UBase_VideoMenu::OnFullscreenButtonClicked);
	WindowedButton->OnButtonClicked.AddDynamic(this, &UBase_VideoMenu::OnWindowedButtonClicked);
	//Display Resolution
	DisplayOneButton->OnButtonClicked.AddDynamic(this, &UBase_VideoMenu::OnResolutionOneButtonClicked);
	DisplayTwoButton->OnButtonClicked.AddDynamic(this, &UBase_VideoMenu::OnResolutionTwoButtonClicked);
	DisplayThreeButton->OnButtonClicked.AddDynamic(this, &UBase_VideoMenu::OnResolutionThreeButtonClicked);
	DisplayFourButton->OnButtonClicked.AddDynamic(this, &UBase_VideoMenu::OnResolutionFourButtonClicked);
	//FPS
	FPSOneButton->OnButtonClicked.AddDynamic(this, &UBase_VideoMenu::OnFPSOneButtonClicked);
	FPSTwoButton->OnButtonClicked.AddDynamic(this, &UBase_VideoMenu::OnFPSTwoButtonClicked);
	FPSThreeButton->OnButtonClicked.AddDynamic(this, &UBase_VideoMenu::OnFPSThreeButtonClicked);
	FPSFourButton->OnButtonClicked.AddDynamic(this, &UBase_VideoMenu::OnFPSFourButtonClicked);

	if (GameInstance)
	{
		//ScreenSize = BaseGameInstance->ScreenSizeInstance;
		Resolution = GameInstance->ResolutionInstance;
		FrameRate = GameInstance->FrameRateInstance;

		/*MasterSlider->SetValue(Master);
		SFXSlider->SetValue(SFX);
		MusicSlider->SetValue(Music);*/
	}
	LoadSettings();
}

void UBase_VideoMenu::OnSoundButtonClicked()
{//Creates Sound Menu
	if (IsValid(SoundMenuClass))
	{
		SoundWidgetMenu = CreateWidget<UBase_SoundMenu>(this, SoundMenuClass);
	}
	if (SoundWidgetMenu != nullptr)
	{
		SoundWidgetMenu->AddToViewport();
		RemoveFromParent();
	}
	else
	{
		UE_LOG(Game, Error, TEXT("SoundWidgetMenu is Invalid (Video) "));
	}
}

void UBase_VideoMenu::OnControlsButtonClicked()
{
	if (IsValid(ControlsMenuClass))
	{
		ControlsWidgetMenu = CreateWidget<UBase_ControlsMenu>(this, ControlsMenuClass);
	}
	if (ControlsWidgetMenu != nullptr)
	{
		ControlsWidgetMenu->AddToViewport();
		RemoveFromParent();
	}
	else
	{
		UE_LOG(Game, Error, TEXT("ControlsWidgetMenu is Invalid (Video)"));
	}
}

void UBase_VideoMenu::OnBackButtonClicked()
{
	if (IsValid(MainMenuClass))
	{
		MainWidgetMenu = CreateWidget<UBase_MainMenu>(this, MainMenuClass);
	}
	if (MainWidgetMenu != nullptr)
	{
		MainWidgetMenu->AddToViewport();
		RemoveFromParent();
	}
	else
	{
		UE_LOG(Game, Error, TEXT("MainWidgetMenu is Invalid (Video) "));
	}
}

void UBase_VideoMenu::OnSaveSettingsButtonClicked()
{
	/*if (IsValid(SaveSettingsMenuClass))
	{
		SaveSettingsWidgetMenu = CreateWidget<UBase_ConfirmationMenu>(this, SaveSettingsMenuClass);
	}
	if (SaveSettingsWidgetMenu != nullptr)
	{
		SaveSettingsWidgetMenu->AddToViewport();
	}
	else
	{
		UE_LOG(MyLog, Error, TEXT("MainWidgetMenu is Invalid (Video) "));
	}*/

	//UGameUserSettings::GetGameUserSettings()->UGameUserSettings::SaveSettings();

	if (GameInstance)
	{
		//BaseGameInstance->ScreenSizeInstance = ScreenSize;
		//GameInstance->ResolutionInstance = Resolution;
		//GameInstance->FrameRateInstance = FrameRate;

		GameInstance->SaveGame();
		LoadSettings();
	}
}
//Screen Size
void UBase_VideoMenu::OnFullscreenButtonClicked()
{
	UE_LOG(Game, Warning, TEXT("Set Fullscreen (Video) "));
	UGameUserSettings::GetGameUserSettings()->UGameUserSettings::SetFullscreenMode(EWindowMode::Fullscreen);
	FullscreenVideo = true;
	WindowedVideo = false;
	ScreenSizeEnabled(false, true);

}

void UBase_VideoMenu::OnWindowedButtonClicked()
{
	UE_LOG(Game, Warning, TEXT("Set Windowed (Video) "));
	UGameUserSettings::GetGameUserSettings()->UGameUserSettings::SetFullscreenMode(EWindowMode::Windowed);
	FullscreenVideo = false;
	WindowedVideo = true;
	ScreenSizeEnabled(true, false);
}
//Display Resolution
void UBase_VideoMenu::OnResolutionOneButtonClicked()
{
	Resolution = (1280, 720);
	UGameUserSettings::GetGameUserSettings()->UGameUserSettings::SetScreenResolution(Resolution);
	GameInstance->ResolutionInstance = Resolution;
	DisplayResolutionEnabled(false, true, true, true);

}

void UBase_VideoMenu::OnResolutionTwoButtonClicked()
{
	Resolution = (1920, 1080);
	UGameUserSettings::GetGameUserSettings()->UGameUserSettings::SetScreenResolution(Resolution);
	GameInstance->ResolutionInstance = Resolution;
	DisplayResolutionEnabled(true, false, true, true);
}

void UBase_VideoMenu::OnResolutionThreeButtonClicked()
{
	Resolution = (2560, 1440);
	UGameUserSettings::GetGameUserSettings()->UGameUserSettings::SetScreenResolution(Resolution);
	GameInstance->ResolutionInstance = Resolution;
	DisplayResolutionEnabled(true, true, false, true);
}

void UBase_VideoMenu::OnResolutionFourButtonClicked()
{
	Resolution = (3840, 2100);
	UGameUserSettings::GetGameUserSettings()->UGameUserSettings::SetScreenResolution(Resolution);
	GameInstance->ResolutionInstance = Resolution;
	DisplayResolutionEnabled(true, true, true, false);
}
//FPS
void UBase_VideoMenu::OnFPSOneButtonClicked()
{
	UGameUserSettings::GetGameUserSettings()->UGameUserSettings::SetFrameRateLimit(30.0f);
	FrameRate = 30.f;
	GameInstance->FrameRateInstance = FrameRate;
	UE_LOG(Game, Error, TEXT("Video: FrameRate: %f"), GameInstance->FrameRateInstance);
	FPSEnabled(false, true, true, true);
}

void UBase_VideoMenu::OnFPSTwoButtonClicked()
{
	UGameUserSettings::GetGameUserSettings()->UGameUserSettings::SetFrameRateLimit(60.0f);
	FrameRate = 60.f;
	GameInstance->FrameRateInstance = FrameRate;
	UE_LOG(Game, Error, TEXT("Video: FrameRate: %f"), GameInstance->FrameRateInstance);
	FPSEnabled(true, false, true, true);
}

void UBase_VideoMenu::OnFPSThreeButtonClicked()
{
	UGameUserSettings::GetGameUserSettings()->UGameUserSettings::SetFrameRateLimit(120.0f);
	FrameRate = 120.f;
	GameInstance->FrameRateInstance = FrameRate;
	UE_LOG(Game, Error, TEXT("Video: FrameRate: %f"), GameInstance->FrameRateInstance);
	FPSEnabled(true, true, false, true);
}

void UBase_VideoMenu::OnFPSFourButtonClicked()
{
	UGameUserSettings::GetGameUserSettings()->UGameUserSettings::SetFrameRateLimit(0.0f);
	FrameRate = 0.f;
	GameInstance->FrameRateInstance = FrameRate;
	FPSEnabled(true, true, true, false);
}
//Sets selected buttons as inactive so user cant select same button again
void UBase_VideoMenu::ScreenSizeEnabled(bool Fullscreen, bool Windowed)
{
	if (!Fullscreen)
	{
		FullscreenButton->SetIsEnabled(false);
		WindowedButton->SetIsEnabled(true);
	}
	if (!Windowed)
	{
		WindowedButton->SetIsEnabled(false);
		FullscreenButton->SetIsEnabled(true);
	}
}

void UBase_VideoMenu::DisplayResolutionEnabled(bool ResOne, bool ResTwo, bool ResThree, bool ResFour)
{
	if (!ResOne)
	{
		DisplayOneButton->SetIsEnabled(false);
		DisplayTwoButton->SetIsEnabled(true);
		DisplayThreeButton->SetIsEnabled(true);
		DisplayFourButton->SetIsEnabled(true);
	}
	if (!ResTwo)
	{
		DisplayOneButton->SetIsEnabled(true);
		DisplayTwoButton->SetIsEnabled(false);
		DisplayThreeButton->SetIsEnabled(true);
		DisplayFourButton->SetIsEnabled(true);
	}
	if (!ResThree)
	{
		DisplayOneButton->SetIsEnabled(true);
		DisplayTwoButton->SetIsEnabled(true);
		DisplayThreeButton->SetIsEnabled(false);
		DisplayFourButton->SetIsEnabled(true);
	}
	if (!ResFour)
	{
		DisplayOneButton->SetIsEnabled(true);
		DisplayTwoButton->SetIsEnabled(true);
		DisplayThreeButton->SetIsEnabled(true);
		DisplayFourButton->SetIsEnabled(false);
	}
}

void UBase_VideoMenu::FPSEnabled(bool FPSOne, bool FPSTwo, bool FPSThree, bool FPSFour)
{
	if (!FPSOne)
	{
		FPSOneButton->SetIsEnabled(false);
		FPSTwoButton->SetIsEnabled(true);
		FPSThreeButton->SetIsEnabled(true);
		FPSFourButton->SetIsEnabled(true);
	}
	if (!FPSTwo)
	{
		FPSOneButton->SetIsEnabled(true);
		FPSTwoButton->SetIsEnabled(false);
		FPSThreeButton->SetIsEnabled(true);
		FPSFourButton->SetIsEnabled(true);
	}
	if (!FPSThree)
	{
		FPSOneButton->SetIsEnabled(true);
		FPSTwoButton->SetIsEnabled(true);
		FPSThreeButton->SetIsEnabled(false);
		FPSFourButton->SetIsEnabled(true);
	}
	if (!FPSFour)
	{
		FPSOneButton->SetIsEnabled(true);
		FPSTwoButton->SetIsEnabled(true);
		FPSThreeButton->SetIsEnabled(true);
		FPSFourButton->SetIsEnabled(false);
	}
}

void UBase_VideoMenu::LoadSettings()
{//Loads setting when game starts up

	UGameUserSettings::GetGameUserSettings()->UGameUserSettings::ApplySettings(false);

	//Selects active buttons for player visuals

	//Screen Size
	if (UGameUserSettings::GetGameUserSettings()->UGameUserSettings::GetFullscreenMode() == EWindowMode::Fullscreen)
	{
		ScreenSizeEnabled(false, true);
	}
	else if (UGameUserSettings::GetGameUserSettings()->UGameUserSettings::GetFullscreenMode() == EWindowMode::Windowed)
	{
		ScreenSizeEnabled(true, false);
	}

	//Display Resolution
	FIntPoint Resolution1 = (1280, 720), Resolution2 = (1920, 1080), Resolution3 = (2560, 1440), Resolution4 = (3840, 2100);

	if (UGameUserSettings::GetGameUserSettings()->UGameUserSettings::GetScreenResolution() == Resolution1)
	{
		DisplayResolutionEnabled(false, true, true, true);
	}
	else if (UGameUserSettings::GetGameUserSettings()->UGameUserSettings::GetScreenResolution() == Resolution2)
	{
		DisplayResolutionEnabled(true, false, true, true);
	}
	else if (UGameUserSettings::GetGameUserSettings()->UGameUserSettings::GetScreenResolution() == Resolution3)
	{
		DisplayResolutionEnabled(true, true, false, true);
	}
	else if (UGameUserSettings::GetGameUserSettings()->UGameUserSettings::GetScreenResolution() == Resolution4)
	{
		DisplayResolutionEnabled(true, true, true, false);
	}

	//FPS
	if (UGameUserSettings::GetGameUserSettings()->GetFrameRateLimit() == 30)
	{
		FPSEnabled(false, true, true, true);
	}
	else if (UGameUserSettings::GetGameUserSettings()->GetFrameRateLimit() == 60)
	{
		FPSEnabled(true, false, true, true);
	}
	else if (UGameUserSettings::GetGameUserSettings()->GetFrameRateLimit() == 120)
	{
		FPSEnabled(true, true, false, true);
	}
	else if (UGameUserSettings::GetGameUserSettings()->GetFrameRateLimit() == 0)
	{
		FPSEnabled(true, true, true, false);
	}
}