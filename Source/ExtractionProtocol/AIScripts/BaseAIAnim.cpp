// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAIAnim.h"
#include "BaseAi.h"

void UBaseAIAnim::NativeInitializeAnimation() {
	Super::NativeInitializeAnimation();

	BaseAi = Cast<ABaseAi>(TryGetPawnOwner());
}

void UBaseAIAnim::NativeUpdateAnimation(float DeltaSeconds) {
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (BaseAi == nullptr) { BaseAi = Cast<ABaseAi>(TryGetPawnOwner()); }
	if (BaseAi == nullptr) { return; }

	//Get Velocity
	FVector Velocity = BaseAi->GetVelocity();
	Velocity.Z = 0;
	Speed = Velocity.Size();

	//Direction
	Direction = CalculateDirection(Velocity, BaseAi->GetActorRotation());

	//Bools
	bIsDead = BaseAi->GetIsDead();
	bIsAttacking = BaseAi->GetIsAttacking();
	bIsHurt = BaseAi->GetIsHurt();
}


//
//void UBaseAIAnim::PlayAttackAnimation() {
//
//}
//
//void UBaseAIAnim::AttackAnimationEnded() {
//	OnAttackEnd.Broadcast();
//}
//
//void UBaseAIAnim::PlayHurtAnimation(float CurrentHealth, float MaxHealth) {
//
//}
//
//void UBaseAIAnim::PlayDeathAnimation(float CurrentHealth, float MaxHealth) {
//
//}
//
//void UBaseAIAnim::DeathFinished() {
//	OnDeath.Broadcast();
//}