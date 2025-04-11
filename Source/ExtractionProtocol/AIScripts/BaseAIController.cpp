// Fill out your copyright notice in the Description page of Project Settings.

//Created Classes
#include "BaseAIController.h"
#include "BaseAi.h"
#include "../ExtractionProtocol.h"
#include "../PlayerScripts/BaseCharacter.h"
//Unreal Classes
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionSystem.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISense_Sight.h"
#include "Perception/AISense_Damage.h"
#include "Net/UnrealNetwork.h"

ABaseAIController::ABaseAIController(const FObjectInitializer& ObjectInitializer) {
	BTComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));
	BBComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackBoardComponent"));
	AIPerception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComponent"));
	
	TeamID = FGenericTeamId(2);
}

void ABaseAIController::BeginPlay() {
	Super::BeginPlay();

	if (AIPerception) {
		AIPerception->OnTargetPerceptionUpdated.AddDynamic(this, &ABaseAIController::PlayerPerceived);
		AIPerception->OnPerceptionUpdated.AddDynamic(this, &ABaseAIController::CurrentPerception);
	}
}

void ABaseAIController::OnPossess(APawn* InPawn) {
	Super::OnPossess(InPawn);

	RunBehaviorTree(BTAsset);
	BTComponent->StartTree(*BTAsset);

	if (BBComponent) {
		BBComponent->InitializeBlackboard(*BTAsset->BlackboardAsset);
	}
}

void ABaseAIController::PlayerPerceived(AActor* Actor, FAIStimulus Stimulus) {
	if (Stimulus.WasSuccessfullySensed()) {
		PerceviedSense = UAIPerceptionSystem::GetSenseClassForStimulus(GetWorld(), Stimulus);
		TSubclassOf<UAISense_Sight> SightConfig;
		TSubclassOf<UAISense_Damage> DamageConfig;
		
		if (GetAttitudeTowards(Actor) == ETeamAttitude::Hostile && PerceviedSense ==SightConfig) {
			//if check for which sense && if player not set
			if (PerceviedSense == SightConfig && !bIsTargetSet) {
				bIsTargetSet = true;
				Target = Cast<ABaseCharacter>(Actor);
				
				BBComponent->SetValueAsObject(TEXT("Player"), Target);
			}

			if (bIsTargetSet) {
				bIsTargetInRange = AttachedAI->IsTargetInRange(Target);

				if (!bIsTargetInRange) {
					BBComponent->ClearValue(TEXT("Player"));

					Target = Cast<ABaseCharacter>(Actor);
					BBComponent->SetValueAsObject(TEXT("Player"), Actor);
				}
			}
		}
		else if(PerceviedSense == DamageConfig)
			BBComponent->SetValueAsVector(TEXT("DamageDestination"), Stimulus.StimulusLocation);
	}
}

void ABaseAIController::CurrentPerception(const TArray<AActor*>& ActorsNearby) {
	//UE_LOG(LogTemp, Error, TEXT("Detected Nearby Actors is: %d"), ActorsNearby.Num());
	TArray<AActor*> PlayerActors;


	if (ActorsNearby.Num() != 0) {
		for (int i = 0; i < ActorsNearby.Num(); i++) {
			if (GetAttitudeTowards(ActorsNearby[i]) == ETeamAttitude::Hostile) {
				PlayerActors.Add(ActorsNearby[i]);
			}
		}

		if (PlayerActors.Num() > 1) {
			AActor* OtherPlayer = nullptr;
			float TargetDist = DistanceFromTarget(Target);
			float OtherTargetDist = 0;
			
			for (int i = 0; i < PlayerActors.Num(); i++) {
				if (Target != PlayerActors[i]) {
					OtherTargetDist = DistanceFromTarget(PlayerActors[i]);
					OtherPlayer = PlayerActors[i];
					break;
				}
			}


			if ((TargetDist > DistanceToChase || OtherTargetDist < TargetDist) && OtherPlayer != nullptr) {
				BBComponent->ClearValue(TEXT("Player"));

				Target = Cast<ABaseCharacter>(OtherPlayer);
				BBComponent->SetValueAsObject(TEXT("Player"), Target);
			}
		}
	}
}
 
ETeamAttitude::Type ABaseAIController::GetTeamAttitudeTowards(const AActor& Other) const {
	const APawn* OtherPawn = Cast<APawn>(&Other);
	if (OtherPawn == nullptr)
		return ETeamAttitude::Neutral;

	IGenericTeamAgentInterface* IActorBot = Cast<IGenericTeamAgentInterface>(OtherPawn->GetController());
	const IGenericTeamAgentInterface* IOtherActor = Cast<IGenericTeamAgentInterface>(&Other);


	FGenericTeamId OtherTeamId = NULL;
	if (IActorBot != nullptr)
		OtherTeamId = IActorBot->GetGenericTeamId();
	else if (IOtherActor != nullptr)
		OtherTeamId = IOtherActor->GetGenericTeamId();

	FGenericTeamId BotTeamId = GetGenericTeamId();
	
	if (OtherTeamId == 255)
		return ETeamAttitude::Neutral;
	else if (OtherTeamId == BotTeamId)
		return ETeamAttitude::Friendly;
	else
		return ETeamAttitude::Hostile;

	return ETeamAttitude::Type();
}

ETeamAttitude::Type ABaseAIController::GetAttitudeTowards(const AActor* Other) const {
	return GetTeamAttitudeTowards(*Other);
}

float ABaseAIController::DistanceFromTarget(AActor* TargetActor) {
	return AttachedAI->GetDistanceTo(TargetActor);
}
