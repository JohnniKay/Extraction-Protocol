// Fill out your copyright notice in the Description page of Project Settings.

//Created Classes
#include "Base_Direction.h"
#include "../Other/Base_DirectionStruct.h"
#include "Components/TextBlock.h"

//Unreal Classes
#include "Components/TextBlock.h"

void UBase_Direction::NativePreConstruct()
{
	//Text->SetText(DirectionInfo.Name.ToString());

	//DirectionInfo.Name.ToString().LeftChop;

	//DirectionInfo.Name = FText::FromName(FName("Kyle is awesome"));
	//GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Blue, FString::Printf(TEXT("Direction Info:  %s"), *DirectionInfo.Name.ToString()));
	
}

void UBase_Direction::NativeConstruct()
{

}
