// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "../ExtractionProtocol.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	ArmorValue = 1.f;
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	
	Owner = GetOwner();
	if (Owner) 
	{ 
		Owner->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::HandleDamage); 		
	}	
}

void UHealthComponent::HandleDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamagedCauser) 
{
	CurrentHealth = FMath::Clamp(CurrentHealth - (Damage * ArmorValue), 0.f, MaxHealth);

	if (CurrentHealth > 0.f) {
		OnDamage.Broadcast(CurrentHealth, MaxHealth);
	}
	else {
		GetOwner()->OnTakeAnyDamage.RemoveDynamic(this, &UHealthComponent::HandleDamage);
		UE_LOG(Game, Warning, TEXT("Actor: %s, Is Dead"), *GetOwner()->GetName());
		OnDeath.Broadcast(CurrentHealth, MaxHealth);
	}

	UE_LOG(Game, Log, TEXT("Actor: %s, CurrentHealth: %f"), *GetOwner()->GetName(), CurrentHealth);
}

void UHealthComponent::SetMaxHealth(float _MaxHealth) {
	MaxHealth = _MaxHealth;
	CurrentHealth = _MaxHealth;
	UE_LOG(Game, Log, TEXT("Actor: %s, CurrentHealth: %f"), *GetOwner()->GetName(), CurrentHealth);
}

void UHealthComponent::SetArmorValue(float _ArmorValue) {
	ArmorValue = _ArmorValue;
	UE_LOG(Game, Log, TEXT("Actor: %s, CurrentArmor: %f"), *GetOwner()->GetName(), ArmorValue);
}