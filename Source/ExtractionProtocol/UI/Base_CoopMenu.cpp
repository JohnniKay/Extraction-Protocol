// Fill out your copyright notice in the Description page of Project Settings.

//Created Classes
#include "Base_CoopMenu.h"
#include "Base_Button.h"
#include "Base_MainMenu.h"
#include "Base_MenuCards.h"
#include "Base_LoadingScreen.h"
#include "../ExtractionProtocol.h"
#include "../Other/Base_GameInstance.h"
#include "Base_MenuController.h"
//Engine Classes
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "MultiplayerSessionsSubsystem.h"
#include "GameFramework/GameUserSettings.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Interfaces/OnlineSessionInterface.h"


void UBase_CoopMenu::NativePreConstruct()
{
	Super::NativePreConstruct();

	GameInstance = Cast<UBase_GameInstance>(GetGameInstance());	

	Time = 15.f;
}

void UBase_CoopMenu::NativeConstruct()
{
	//Co-op Menu
	//SoloButton->OnButtonClicked.AddDynamic(this, &UBase_CoopMenu::OnSoloButtonClicked);
	//HostButton->OnButtonClicked.AddDynamic(this, &UBase_CoopMenu::OnHostButtonClicked);
	//JoinButton->OnButtonClicked.AddDynamic(this, &UBase_CoopMenu::OnJoinButtonClicked);
	//BackButton->OnButtonClicked.AddDynamic(this, &UBase_CoopMenu::OnBackButtonClicked);	

	if(SoloButton) SoloButton->OnButtonClicked.AddDynamic(this, &UBase_CoopMenu::OnSoloButtonClicked);
	if(HostButton) HostButton->OnButtonClicked.AddDynamic(this, &UBase_CoopMenu::OnHostButtonClicked);
	if(JoinButton) JoinButton->OnButtonClicked.AddDynamic(this, &UBase_CoopMenu::OnJoinButtonClicked);
	if(BackButton) BackButton->OnButtonClicked.AddDynamic(this, &UBase_CoopMenu::OnBackButtonClicked);		
}

void UBase_CoopMenu::MenuSetup(int32 NumberOfPublicConnections, FString TypeOfMatch, FString LobbyPath)
{
	PathToLobby = FString::Printf(TEXT("%s?listen"), *LobbyPath); // Adds listen option to file path
	NumPublicConnections = NumberOfPublicConnections;
	MatchType = TypeOfMatch;
	//AddToViewport();
	SetVisibility(ESlateVisibility::Visible);
	bIsFocusable = true;

	/*UWorld* World = GetWorld();
	if (World)
	{
		APlayerController* PlayerController = World->GetFirstPlayerController();

		if (PlayerController)
		{
			FInputModeUIOnly InputModeData;
			InputModeData.SetWidgetToFocus(TakeWidget());
			InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
			PlayerController->SetInputMode(InputModeData);
			PlayerController->SetShowMouseCursor(true);
		}
	}*/

	UGameInstance* GameInstance2 = GetGameInstance();
	GameInstance2 = GetGameInstance();
	if (GameInstance2)
	{
		MultiplayerSessionsSubsystem = GameInstance2->GetSubsystem<UMultiplayerSessionsSubsystem>();		
	}

	if (MultiplayerSessionsSubsystem)
	{
		MultiplayerSessionsSubsystem->MultiplayerOnCreateSessionComplete.AddDynamic(this, &ThisClass::OnCreateSession);
		MultiplayerSessionsSubsystem->MultiplayerOnFindSessionsComplete.AddUObject(this, &ThisClass::OnFindSessions);
		MultiplayerSessionsSubsystem->MultiplayerOnJoinSessionComplete.AddUObject(this, &ThisClass::OnJoinSession);
		MultiplayerSessionsSubsystem->MultiplayerOnDestroySessionComplete.AddDynamic(this, &ThisClass::OnDestroySession);
		MultiplayerSessionsSubsystem->MultiplayerOnStartSessionComplete.AddDynamic(this, &ThisClass::OnStartSession);	

	}	
}

bool UBase_CoopMenu::Initialize()
{
	if (!Super::Initialize()) return false;
		
	return true;
}

void UBase_CoopMenu::NativeDestruct()
{
	MenuDestruct();

	Super::NativeDestruct();
}

void UBase_CoopMenu::OnCreateSession(bool bWasSuccessful)
{
	if (bWasSuccessful)
	{		
		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, FString::Printf(TEXT("Loading Level: %s"), *PathToLobby));

		UWorld* World = GetWorld();
		if (World)
		{
			bool TravelSuccess = World->ServerTravel(PathToLobby);
			if(!TravelSuccess) { GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, FString(TEXT("Failed to Create Session"))); }
		}
	}
	else
	{
		// Enables button to be used if session failed to create
		HostButton->SetIsEnabled(true);

		//GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, FString(TEXT("Failed to Create Session")));
	}
}

void UBase_CoopMenu::OnFindSessions(const TArray<FOnlineSessionSearchResult>& SessionResults, bool bWasSuccessful)
{
	if (MultiplayerSessionsSubsystem == nullptr) return;

	// Iterate through SearchResults to find session with same MatchType
	for (auto Result : SessionResults)
	{
		FString SettingsValue;		

		Result.Session.SessionSettings.Get(FName("Default"), SettingsValue);		
		UE_LOG(LogTemp, Error, TEXT("Session Result: %s, Line: %s"), *SettingsValue, *FString::FromInt(__LINE__));

		if (SettingsValue == MatchType)
		{
			MultiplayerSessionsSubsystem->JoinSession(Result);
			return;
		}
	}

	// Enables button to be used if no sessions were found 
	if (!bWasSuccessful || SessionResults.Num() == 0)
	{
		JoinButton->SetIsEnabled(true);
		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, FString::Printf(TEXT("Failed To Find Sessions!, %s.cpp:(%s)"), *FString(__FUNCTION__), *FString::FromInt(__LINE__)));

	}
}

void UBase_CoopMenu::OnJoinSession(EOnJoinSessionCompleteResult::Type Result)
{
	IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get();

	if (Subsystem)
	{
		IOnlineSessionPtr SessionInterface = Subsystem->GetSessionInterface();
		if (SessionInterface.IsValid())
		{
			FString Address;
			SessionInterface->GetResolvedConnectString(NAME_GameSession, Address);

			// Gets Player Controller from Player List
			APlayerController* PlayerController = GetGameInstance()->GetFirstLocalPlayerController();
			if (PlayerController)
			{
				// Joins Session of Address 
				PlayerController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
			}
		}
	}

	if (Result != EOnJoinSessionCompleteResult::Success)
	{
		JoinButton->SetIsEnabled(true);
		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, FString(TEXT("Failed to Join Session")));
	}
}

void UBase_CoopMenu::OnDestroySession(bool bWasSuccessful)
{
}

void UBase_CoopMenu::OnStartSession(bool bWasSuccessful)
{
}

void UBase_CoopMenu::MenuDestruct()
{
	RemoveFromParent();
	UWorld* World = GetWorld();

	if (World)
	{
		APlayerController* PlayerController = World->GetFirstPlayerController();

		if (PlayerController)
		{
			/*FInputModeGameOnly InputModeData;
			PlayerController->SetInputMode(InputModeData);
			PlayerController->SetShowMouseCursor(false);*/
		}
	}
}

void UBase_CoopMenu::OnSoloButtonClicked()
{
	GameInstance->UBase_GameInstance::LoadLoadingScreen();


	//if (IsValid(LoadingScreenClass))
	//{
	//	LoadingScreenWidgetMenu = CreateWidget<UBase_LoadingScreen>(this, LoadingScreenClass);
	//}
	//if (LoadingScreenWidgetMenu != nullptr)
	//{
	//	LoadingScreenWidgetMenu->AddToViewport();
	//	GameInstance->UBase_GameInstance::LoadFirstLevel();
	//	RemoveFromParent();

	//	/*FTimerHandle Timer;
	//	GetWorld()->GetTimerManager().SetTimer(Timer, GameInstance, &UBase_GameInstance::LoadFirstLevel, Time);*/
	//	UE_LOG(Game, Error, TEXT("RemovedFromParent "));
	//}
	//else
	//{
	//	UE_LOG(Game, Error, TEXT("LoadingScreenWidgetMenu is Invalid "));
	//}
}

void UBase_CoopMenu::OnHostButtonClicked()
{
	// Disables button onces pressed. This way we cannot spawm it and cause the functions to be called multiple times
	HostButton->SetIsEnabled(false);
	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Cyan, FString::Printf(TEXT("Starting Host Session...")));

	if (MultiplayerSessionsSubsystem)
	{
		MultiplayerSessionsSubsystem->CreateSession(NumPublicConnections, MatchType);				
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, FString::Printf(TEXT("Failed to Host Session!")));
	}

}

void UBase_CoopMenu::OnJoinButtonClicked()
{
	// Disables button onces pressed. This way we cannot spawm it and cause the functions to be called multiple times
	JoinButton->SetIsEnabled(false);

	if (MultiplayerSessionsSubsystem)
	{
		// Since DevAppID = 480, search results must be higher to accommodate other developers using the same ID
		MultiplayerSessionsSubsystem->FindSessions(10000);
		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Cyan, FString::Printf(TEXT("Finding Sessions...")));
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, FString::Printf(TEXT("Failed to find valid Sessions.")));
	}
}

void UBase_CoopMenu::OnBackButtonClicked()
{
	if (IsValid(MenuClass))
	{
		WidgetMenu = CreateWidget<UBase_MainMenu>(this, MenuClass);
	}
	if (WidgetMenu != nullptr)
	{
		WidgetMenu->AddToViewport();
		RemoveFromParent();
	}
	else
	{
		UE_LOG(Game, Error, TEXT("MainWidgetMenu is Invalid "));
	}	
}