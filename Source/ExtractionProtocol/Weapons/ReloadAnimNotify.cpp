// Fill out your copyright notice in the Description page of Project Settings.


#include "ReloadAnimNotify.h"
#include "ExtractionProtocol/PlayerScripts/BaseCharacterAnim.h"

void UReloadAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	ReloadNotify = Cast<UBaseCharacterAnim>(MeshComp->GetAnimInstance());

	if (!ReloadNotify) { return; }

	ReloadNotify->OnReloadWeapon.Broadcast();
}
