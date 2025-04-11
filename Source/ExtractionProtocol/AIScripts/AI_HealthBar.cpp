// Fill out your copyright notice in the Description page of Project Settings.


#include "AI_HealthBar.h"

#include "Components/Progressbar.h"

void UAI_HealthBar::SetHealth(float CurrentHealth, float MaxHealth) {
	if (MaxHealth != 0.f) {
		HealthBar->SetPercent(CurrentHealth / MaxHealth);
	}
}