// Fill out your copyright notice in the Description page of Project Settings.


#include "Base_MenuCards.h"
#include "../ExtractionProtocol.h"
//Unreal Classes
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Animation/WidgetAnimation.h"

void UBase_MenuCards::NativePreConstruct()
{
    TitleText->SetText(TitleButtonText);
    InfoText->SetText(InfoButtonText);
    Time = 0.1f;
}

void UBase_MenuCards::NativeConstruct()
{
    Button->OnClicked.AddDynamic(this, &UBase_MenuCards::OnClicked);
    Button->OnHovered.AddDynamic(this, &UBase_MenuCards::OnHovered);
    Button->OnUnhovered.AddDynamic(this, &UBase_MenuCards::OnUnHovered);
}

void UBase_MenuCards::OnClicked()
{
    UGameplayStatics::PlaySound2D(GetWorld(), ClickSound);
    UE_LOG(Game, Warning, TEXT("Button Clicked"));
    FTimerHandle Timer;
    GetWorld()->GetTimerManager().SetTimer(Timer, this, &UBase_MenuCards::ClickTimerDelay, Time);
}

void UBase_MenuCards::OnHovered()
{
    UGameplayStatics::PlaySound2D(GetWorld(), HoverSound);

    PlayAnimation(ScaleAnimation, 0.0f, 1, EUMGSequencePlayMode::Forward, 1.0f, false);
}

void UBase_MenuCards::OnUnHovered()
{
    PlayAnimation(ScaleAnimation, 0.0f, 1, EUMGSequencePlayMode::Reverse, 1.0f, false);
}

void UBase_MenuCards::ClickTimerDelay()
{
    OnButtonClicked.Broadcast();
}

