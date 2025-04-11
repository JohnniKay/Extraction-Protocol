// Fill out your copyright notice in the Description page of Project Settings.


#include "GruntAnim.h"
#include "../ExtractionProtocol.h"

//void UGruntAnim::PlayAttackAnimation() {
//	int rng = FMath::RandRange(0, AttackAssets.Num() - 1);
//	CurretAttackAsset = AttackAssets[rng];
//
//	PlaySlotAnimationAsDynamicMontage(CurretAttackAsset, TEXT("Attack"));
//	GetWorld()->GetTimerManager().SetTimer(AttackHandle, this, &UGruntAnim::AttackAnimationEnded, CurretAttackAsset->GetPlayLength());
//}
//
//void UGruntAnim::AttackAnimationEnded() {
//	Super::AttackAnimationEnded();
//}
//
//void UGruntAnim::PlayHurtAnimation(float CurrentHealth, float MaxHealth) {
//	int rng = FMath::RandRange(0, HurtAssets.Num() - 1);
//	CurrentHurtAsset = HurtAssets[rng];
//
//	PlaySlotAnimationAsDynamicMontage(CurrentHurtAsset, TEXT("Hurt"));
//}
//
//void UGruntAnim::PlayDeathAnimation(float CurrentHealth, float MaxHealth) {
//	int rng = FMath::RandRange(0, DeathAssets.Num() - 1);
//	CurrentDeathAsset = DeathAssets[rng];
//
//	USkeletalMeshComponent* Mesh = GetSkelMeshComponent();
//	if (Mesh)
//		Mesh->PlayAnimation(CurrentDeathAsset, false);
//
//	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UGruntAnim::DeathFinished, CurrentDeathAsset->GetPlayLength());
//}
//
//void UGruntAnim::DeathFinished() {
//	Super::DeathFinished();
//}