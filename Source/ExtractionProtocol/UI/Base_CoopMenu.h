// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "Base_CoopMenu.generated.h"

/**
 * 
 */
UCLASS()
class EXTRACTIONPROTOCOL_API UBase_CoopMenu : public UUserWidget
{
	GENERATED_BODY()
	
public:

	//Co-op Menu buttons
	UPROPERTY(BlueprintReadWrite, Category = "Button", meta = (BindWidget))
		class UBase_MenuCards* SoloButton;

	UPROPERTY(BlueprintReadWrite, Category = "Button", meta = (BindWidget))
		class UBase_MenuCards* HostButton;

	UPROPERTY(BlueprintReadWrite, Category = "Button", meta = (BindWidget))
		class UBase_MenuCards* JoinButton;

	UPROPERTY(BlueprintReadWrite, Category = "Button", meta = (BindWidget))
		class UBase_Button* BackButton;

	//GameInstance
	UPROPERTY(BlueprintReadWrite, Category = "Game Instance")
		class UBase_GameInstance* GameInstance;

	//Main Menu 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Menu")
		TSubclassOf<class UBase_MainMenu> MenuClass;

	UPROPERTY(BlueprintReadWrite, Category = "Menu")
		class UBase_MainMenu* WidgetMenu;

	//Loading Screen
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Menu")
		TSubclassOf<class UBase_LoadingScreen> LoadingScreenClass;

	UPROPERTY(BlueprintReadWrite, Category = "Menu")
		class UBase_LoadingScreen* LoadingScreenWidgetMenu;

	float Time;

private:

	int32 NumPublicConnections{ 2 };
	FString MatchType{ TEXT("Default") };
	FString PathToLobby{ TEXT("") };

	// The Subsystem designed to handle all online session funcitonality
	class UMultiplayerSessionsSubsystem* MultiplayerSessionsSubsystem;

public:

	virtual void NativePreConstruct() override;

	virtual void NativeConstruct();

	//Co-op Menu
	UFUNCTION()
		void OnSoloButtonClicked();

	UFUNCTION()
		void OnHostButtonClicked();

	UFUNCTION()
		void OnJoinButtonClicked();

	UFUNCTION()
		void OnBackButtonClicked();

	//Multiplayer
	UFUNCTION(BlueprintCallable)
		void MenuSetup(int32 NumberOfPublicConnections = 2, FString TypeOfMatch = FString(TEXT("Default")), FString LobbyPath = FString(TEXT("")));



protected:
	virtual bool Initialize() override;
	virtual void NativeDestruct() override;

	//
	// Callbacks for Custom Delegates on MultiplayerSessionSubsystem 
	//
	UFUNCTION()
	void OnCreateSession(bool bWasSuccessful);
	void OnFindSessions(const TArray<FOnlineSessionSearchResult>& SessionResults, bool bWasSuccessful);
	void OnJoinSession(EOnJoinSessionCompleteResult::Type Result);
	UFUNCTION()
		void OnDestroySession(bool bWasSuccessful);
	UFUNCTION()
		void OnStartSession(bool bWasSuccessful);

	void MenuDestruct();


};
