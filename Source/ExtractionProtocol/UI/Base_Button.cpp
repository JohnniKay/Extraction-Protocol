
// Fill out your copyright notice in the Description page of Project Settings.


#include "Base_Button.h"
#include "../ExtractionProtocol.h"
//Unreal Classes
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Animation/WidgetAnimation.h"

void UBase_Button::NativePreConstruct()
{
	Info->SetText(ButtonText);
	Time = 0.1f;
}

void UBase_Button::NativeConstruct()
{
	Button->OnClicked.AddDynamic(this, &UBase_Button::OnClicked);
	Button->OnHovered.AddDynamic(this, &UBase_Button::OnHovered);
	Button->OnUnhovered.AddDynamic(this, &UBase_Button::OnUnhovered);
}

void UBase_Button::OnClicked()
{
	UGameplayStatics::PlaySound2D(GetWorld(), ClickSound);
	FTimerHandle Timer;
	GetWorld()->GetTimerManager().SetTimer(Timer, this, &UBase_Button::ClickTimerDelay, Time);
	UE_LOG(Game, Warning, TEXT("Button Clicked"));
}

void UBase_Button::OnHovered()
{
	UGameplayStatics::PlaySound2D(GetWorld(), HoverSound);

	PlayAnimation(ScaleAnimation, 0.0f, 1, EUMGSequencePlayMode::Forward, 1.0f, false);
}

void UBase_Button::OnUnhovered()
{
	PlayAnimation(ScaleAnimation, 0.0f, 1, EUMGSequencePlayMode::Reverse, 1.0f, false);
}

void UBase_Button::ClickTimerDelay()
{
	OnButtonClicked.Broadcast();
}
