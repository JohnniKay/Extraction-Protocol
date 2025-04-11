// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacterAnim.h"
#include "BaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "../Weapons/Base_Weapon.h"

void UBaseCharacterAnim::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	BaseCharacter = Cast<ABaseCharacter>(TryGetPawnOwner());
}

void UBaseCharacterAnim::NativeUpdateAnimation(float DeltaSeconds)
{
	// Since this is an override, we must call parent class
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (BaseCharacter == nullptr) { BaseCharacter = Cast<ABaseCharacter>(TryGetPawnOwner()); }
	if (BaseCharacter == nullptr) { return; }

	FVector Velocity = BaseCharacter->GetVelocity();
	Velocity.Z = 0.f;
	Speed = Velocity.Size();

	Direction = CalculateDirection(Velocity, BaseCharacter->GetActorRotation());
	bIsInAir = BaseCharacter->GetCharacterMovement()->IsFalling();	
	bIsAccelerating = BaseCharacter->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0.f ? true : false;
	bWeaponEquipped = BaseCharacter->IsWeaponEquipped();
	EquippedWeapon = BaseCharacter->GetEquippedWeapon();
	bIsCrouched = BaseCharacter->bIsCrouched;
	bIsDead = BaseCharacter->GetIsDead();
	bIsHurt = BaseCharacter->GetIsHurt();
	bIsShooting = BaseCharacter->GetIsShooting();
	bIsReloading = BaseCharacter->GetIsReloading();	
	AO_Yaw = BaseCharacter->GetAO_Yaw();
	AO_Pitch = BaseCharacter->GetAO_Pitch();

	// Unedited working version: 	
	//// Used to lock left hand to weapon Left Hand Weapon Socket
	//if (bWeaponEquipped && EquippedWeapon && EquippedWeapon->GetWeaponMesh() && BaseCharacter->GetMesh() && BaseCharacter->ThirdPersonMesh)
	//{
	//	LeftHandTransform = EquippedWeapon->GetWeaponMesh()->GetSocketTransform(FName("LeftHandSocket", ERelativeTransformSpace::RTS_World));
	//	FVector OutPosition;
	//	FRotator OutRotation;

	//	// Needs to be for both First Person Mesh and Third Person Mesh
	//	BaseCharacter->ThirdPersonMesh->TransformToBoneSpace(FName("hand_r"), LeftHandTransform.GetLocation(), FRotator::ZeroRotator, OutPosition, OutRotation);
	//	BaseCharacter->GetMesh()->TransformToBoneSpace(FName("hand_r"), LeftHandTransform.GetLocation(), FRotator::ZeroRotator, OutPosition, OutRotation);

	//	LeftHandTransform.SetLocation(OutPosition);
	//	LeftHandTransform.SetRotation(FQuat(OutRotation));
	//}


	// Used to lock left hand to weapon Left Hand Weapon Socket
	if (bWeaponEquipped && EquippedWeapon && EquippedWeapon->GetWeaponMesh() && BaseCharacter->GetMesh() && BaseCharacter->ThirdPersonMesh)
	{
		LeftHandTransform = EquippedWeapon->GetWeaponMesh()->GetSocketTransform(FName("LeftHandSocket", ERelativeTransformSpace::RTS_World));		

		FVector OutPosition;
		FRotator OutRotation;

		// Needs to be for both First Person Mesh and Third Person Mesh
		//BaseCharacter->ThirdPersonMesh->TransformToBoneSpace(FName("hand_r"), LeftHandTransform.GetLocation(), FRotator::ZeroRotator, OutPosition, OutRotation);
		BaseCharacter->GetMesh()->TransformToBoneSpace(FName("hand_r"), LeftHandTransform.GetLocation(), FRotator::ZeroRotator, OutPosition, OutRotation);

		LeftHandTransform.SetLocation(OutPosition);
		LeftHandTransform.SetRotation(FQuat(OutRotation));
		
	}
}