// Fill out your copyright notice in the Description page of Project Settings.


#include "OverheadWidget.h"
#include "Components/TextBlock.h"
#include "GameFramework/PlayerState.h"

void UOverheadWidget::DisplayPlayerName(APawn* InPawn)
{
	if (DisplayName)
	{		
		// Will try to get Player Name for 30s after Initialization 
		float Timeout = 30.f;
		float Interval = 0.1f;
		float TotalTime = -0.1f;

		if (!InPawn->GetPlayerState() || !*InPawn->GetPlayerState()->GetPlayerName() && TotalTime < Timeout)
		{
			FTimerHandle TimerHandle;
			FTimerDelegate RetryFunction;			

			RetryFunction.BindUFunction(this, FName("DisplayPlayerName"), InPawn);
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, RetryFunction, Interval, false, 0.1f);
			TotalTime += Interval;
			return;
		}		
		DisplayName->SetText(FText::FromString(InPawn->GetPlayerState()->GetPlayerName()));
	}	
}

FString UOverheadWidget::GetPlayerNetRole(APawn* InPawn)
{
	ENetRole LocalRole = InPawn->GetLocalRole();
	switch (LocalRole)
	{
	case ENetRole::ROLE_Authority:
		return FString("ROLE_Authority");
			break;			
	case ENetRole::ROLE_AutonomousProxy:
		return FString("ROLE_AutonomousProxy");
			break;
	case ENetRole::ROLE_SimulatedProxy:
		return FString("ROLE_SimulatedProxy");
			break;
	case ENetRole::ROLE_None:
		return FString("ROLE_None");
			break;
	}
	return FString();
}
