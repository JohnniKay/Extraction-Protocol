// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "BaseAIAnim.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBaseAIAnimNotify);
/**
 * 
 */
UCLASS(ABSTRACT)
class EXTRACTIONPROTOCOL_API UBaseAIAnim : public UAnimInstance
{
	GENERATED_BODY()

protected:
	virtual void NativeInitializeAnimation() override;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

public:
	UPROPERTY(BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
		float Speed;

	UPROPERTY(BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
		float Direction;

	UPROPERTY(BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
		class ABaseAi* BaseAi;

private:
	UPROPERTY(BlueprintReadOnly, Category = Bools, meta = (AllowPrivateAccess = "true"))
		bool bIsDead;

	UPROPERTY(BlueprintReadOnly, Category = Bools, meta = (AllowPrivateAccess = "true"))
		bool bIsHurt;

	UPROPERTY(BlueprintReadOnly, Category = Bools, meta = (AllowPrivateAccess = "true"))
		bool bIsAttacking;

	//UFUNCTION()
	//	virtual void PlayAttackAnimation();

	//UFUNCTION()
	//	virtual void AttackAnimationEnded();

	//UFUNCTION()
	//	virtual void PlayHurtAnimation(float CurrentHealth, float MaxHealth);

	//UFUNCTION()
	//	virtual void PlayDeathAnimation(float CurrentHealth, float MaxHealth);

	//UFUNCTION()
	//	virtual void DeathFinished();

	////Death Notify
	//UPROPERTY(VisibleAnywhere, BluePrintReadWrite, Category = "Animations")
	//	FBaseAIAnimNotify OnDeath;

	//UPROPERTY(VisibleAnywhere, BluePrintReadWrite, Category = "Animations")
	//	FBaseAIAnimNotify OnAttackEnd;

	////Movement Speed and Directions
	////UPROPERTY(VisibleAnywhere, BluePrintReadWrite, Category = "Movement")
	////	float Direction;

	////UPROPERTY(VisibleAnywhere, BluePrintReadWrite, Category = "Movement")
	////	float Speed;

	////Animations
	//UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Animations")
	//	TArray<UAnimSequence*> AttackAssets;

	//UPROPERTY(VisibleAnywhere, BluePrintReadWrite, Category = "Animations")
	//	UAnimSequence* CurretAttackAsset;

	//UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Animations")
	//	FName AttackSlot;

	//UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Animations")
	//	TArray<UAnimSequence*> HurtAssets;

	//UPROPERTY(VisibleAnywhere, BluePrintReadWrite, Category = "Animations")
	//	UAnimSequence* CurrentHurtAsset;

	//UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Animations")
	//	FName HurtSlot;

	//UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Animations")
	//	TArray<UAnimSequence*> DeathAssets;

	//UPROPERTY(VisibleAnywhere, BluePrintReadWrite, Category = "Animations")
	//	UAnimSequence* CurrentDeathAsset;

	//UPROPERTY(VisibleAnywhere, BluePrintReadWrite, Category = "Animations")
	//	bool bIsDead{ false };

	//FTimerHandle TimerHandle;

	//FTimerHandle AttackHandle;
};
