// Fill out your copyright notice in the Description page of Project Settings.

//Created Classes
#include "Base_TabButton.h"
#include "../ExtractionProtocol.h"
//Unreal Classes
#include "Components/Border.h"
#include "Components/Button.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Animation/WidgetAnimation.h"

void UBase_TabButton::NativePreConstruct()
{
	Info->SetText(ButtonText);
}

void UBase_TabButton::NativeConstruct()
{
	Button->OnClicked.AddDynamic(this, &UBase_TabButton::OnClicked);
	Button->OnHovered.AddDynamic(this, &UBase_TabButton::OnHovered);
}

void UBase_TabButton::OnClicked()
{
	UGameplayStatics::PlaySound2D(GetWorld(), ClickSound);
	UE_LOG(Game, Warning, TEXT("TabButton Clicked"));
	
	OnButtonClicked.Broadcast();
}

void UBase_TabButton::OnHovered()
{
	//FLinearColor Color; Color.R = 0.2f; Color.G = 1.0f; Color.B = 0.0f; Color.A = 0.3f;
	UGameplayStatics::PlaySound2D(GetWorld(), ClickSound);
	PlayAnimation(Hover1);
	//Border->SetBrushColor(Color);
}

void UBase_TabButton::OnUnhovered()
{
	//FLinearColor Color; Color.R = 1.0f; Color.G = 0.33f; Color.B = 0.04; Color.A = 0.3f;
	PlayAnimation(Hover1, EUMGSequencePlayMode::Reverse);
	//Border->SetBrushColor(Color);
}
