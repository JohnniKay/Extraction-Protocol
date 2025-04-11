// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAi.h"
//Created Classes
#include "../Component/HealthComponent.h"
#include "BaseAIAnim.h"
#include "BaseAIController.h"
#include "../PlayerScripts/BaseCharacter.h"
#include "../ExtractionProtocol.h"
#include "AI_HealthBar.h"
#include "AI_CreatureName.h"
//Unreal Classes
#include "./GameFramework/CharacterMovementComponent.h"
#include "./Components/CapsuleComponent.h"
#include "BrainComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/Gameplaystatics.h"
#include "Net/UnrealNetwork.h"
#include "Components/WidgetComponent.h"


// Sets default values
ABaseAi::ABaseAi()
{
	PrimaryActorTick.bCanEverTick = true;
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	HealthComponent->SetMaxHealth(1.0f);
	HealthComponent->SetIsReplicated(true);

	OverHeadHealthBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthBar"));
	OverHeadHealthBar->SetupAttachment(RootComponent);
	OverHeadHealthBar->SetWidgetSpace(EWidgetSpace::Screen);
	
	OverHeadName = CreateDefaultSubobject<UWidgetComponent>(TEXT("AiName"));
	OverHeadName->SetupAttachment(RootComponent);
	OverHeadName->SetWidgetSpace(EWidgetSpace::Screen);
}

// Called when the game starts or when spawned
void ABaseAi::BeginPlay()
{
	Super::BeginPlay();
	AIController = Cast<ABaseAIController>(GetController());
	if (AIController != nullptr) {
		BrainComponent = AIController->GetBrainComponent();
		BBComponent = AIController->GetBlackboardComponent();
	}
	EVisible = ESlateVisibility::Hidden;

	HealthBarWidget = Cast<UAI_HealthBar>(OverHeadHealthBar->GetUserWidgetObject());
	if (HealthBarWidget) {
		HealthBarWidget->SetVisibility(EVisible);
	}

	NameWidget = Cast<UAI_CreatureName>(OverHeadName->GetUserWidgetObject());
	if (NameWidget) {
		NameWidget->SetText(CreatureStruct.Name);
		NameWidget->SetVisibility(EVisible);
	}

	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	GetMesh()->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);

	SetReferencesAndBind();
}

void ABaseAi::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABaseAi, bIsDead);
	DOREPLIFETIME(ABaseAi, bIsAttacking);
	DOREPLIFETIME(ABaseAi, bIsHurt);

	DOREPLIFETIME(ABaseAi, EVisible);
	DOREPLIFETIME(ABaseAi, NameWidget);
	DOREPLIFETIME(ABaseAi, HealthBarWidget);
}

void ABaseAi::MeleePlayer(FHitResult OutHit) {}

void ABaseAi::MeleeAttackFinished() {
	bIsAttacking = false;
}

void ABaseAi::SetController() {}

bool ABaseAi::IsTargetInRange(AActor* Target) {
	float distance = Target->GetDistanceTo(this);

	if (distance < AIController->TargetDistance) {
		return true;
	}
	else {
		return false;
	}
}

void ABaseAi::TurnOffHud() {
	EVisible = ESlateVisibility::Hidden;
	NameWidget->SetVisibility(EVisible);
	HealthBarWidget->SetVisibility(EVisible);
}

void ABaseAi::CharacterDeath(float CurrentHealth, float MaxHealth) {
	bIsHurt = false;
	bIsDead = true;
	HealthBarWidget->SetHealth(0, 1);
	GetCharacterMovement()->StopMovementImmediately();
	GetCharacterMovement()->GravityScale = 0.f;
	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECR_Ignore);
}

void ABaseAi::CharacterDeathFinished() {}

void ABaseAi::CharacterNoLongerHurt() {
	bIsHurt = false;
}

void ABaseAi::CharacterHurt(float CurrentHealth, float MaxHealth) {
	if (HealthComponent->CurrentHealth > 0.f) {
		EVisible = ESlateVisibility::Visible;
		HealthBarWidget->SetHealth(HealthComponent->CurrentHealth, HealthComponent->MaxHealth);
		NameWidget->SetVisibility(EVisible);
		HealthBarWidget->SetVisibility(EVisible);
		if (AIController) {
			bIsHurt = true;
		}
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ABaseAi::CharacterNoLongerHurt, .1f);
		GetWorld()->GetTimerManager().SetTimer(HUDHandle, this, &ABaseAi::TurnOffHud, 3.f);
		//GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Magenta, FString::Printf(TEXT("Base AI has taken Damage")));
	}
}

void ABaseAi::SetReferencesAndBind() {
	AnimBP = Cast<UBaseAIAnim>(GetMesh()->GetAnimInstance());

	//Play Hurt Animations
	HealthComponent->OnDamage.AddDynamic(this, &ABaseAi::CharacterHurt);
	
	//Start Death Calls
	HealthComponent->OnDeath.AddDynamic(this, &ABaseAi::CharacterDeath);
}