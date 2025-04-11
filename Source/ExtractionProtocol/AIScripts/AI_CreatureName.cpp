// Fill out your copyright notice in the Description page of Project Settings.


#include "AI_CreatureName.h"

#include "Components/TextBlock.h"

void UAI_CreatureName::SetText(FText _CreatureName) {
	CreatureName->SetText(_CreatureName);
}