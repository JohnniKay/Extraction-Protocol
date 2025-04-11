// Fill out your copyright notice in the Description page of Project Settings.

//Created Classes
#include "GruntAI.h"
#include "BaseAi.h"
#include "BaseAIController.h"
#include "BaseAIAnim.h"
#include "../Component/HealthComponent.h"
#include "../ExtractionProtocol.h"
//Unreal Classes
#include "./GameFramework/CharacterMovementComponent.h"
#include "BrainComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Engine/DamageEvents.h"

AGruntAI::AGruntAI() {
	//Setting the health component
	if (HealthComponent)
	{
		HealthComponent->SetMaxHealth(200.f);
	}
}

void AGruntAI::BeginPlay() {
	Super::BeginPlay();
	if (AIController != nullptr && AIController->AttachedAI == nullptr) {
		SetController();
	}

	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	GetMesh()->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);

	GetCharacterMovement()->MaxWalkSpeed = CreatureStruct.WalkSpeed;
	HealthComponent->SetMaxHealth(CreatureStruct.Health);

}

void AGruntAI::MeleePlayer(FHitResult OutHit) {
	Super::MeleePlayer(OutHit);
	bIsAttacking = true;

	//GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECR_Ignore);
	GetMesh()->SetCollisionResponseToAllChannels(ECR_Ignore);
	GetCharacterMovement()->StopMovementImmediately();

	OutHit.GetActor()->TakeDamage(CreatureStruct.MeleeDamage, FDamageEvent(), OutHit.GetActor()->GetInstigatorController(), OutHit.GetActor()->GetInstigator());

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ABaseAi::MeleeAttackFinished, 0.75f);
}

void AGruntAI::MeleeAttackFinished() {
	bIsAttacking = false;
}

void AGruntAI::CharacterDeath(float CurrentHealth, float MaxHealth) {
	Super::CharacterDeath(CurrentHealth, MaxHealth);
	BrainComponent->StopLogic(TEXT("The AI is dead"));

	int rng = FMath::RandRange(1, 6);
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AGruntAI::CharacterDeathFinished, rng);
}

void AGruntAI::CharacterDeathFinished() {
	K2_DestroyActor();
}

void AGruntAI::SetController() {
	AIController->AttachedAI = this;
}