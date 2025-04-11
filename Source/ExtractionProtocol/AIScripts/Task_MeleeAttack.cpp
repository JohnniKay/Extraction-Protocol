// Fill out your copyright notice in the Description page of Project Settings.

//Created Classes
#include "Task_MeleeAttack.h"
#include "BaseAIController.h"
#include "BaseAi.h"
#include "../PlayerScripts\BaseCharacter.h"
#include "../ExtractionProtocol.h"
//Unreal Classes
#include "NavigationSystem.h"
#include "BehaviorTree//BlackboardComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "KIsmet/Gameplaystatics.h"

EBTNodeResult::Type UTask_MeleeAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
	//Super::ExecuteTask(OwnerComp, NodeMemory);

	//Get AI Controller
	ABaseAIController* AIController = Cast<ABaseAIController>(OwnerComp.GetAIOwner());

	//Get Actor Reference
	ABaseAi* AI = Cast<ABaseAi>(AIController->GetPawn());

	Radius = 50.f;

	//Set Start and End Point
	FVector StartPoint = AIController->GetPawn()->GetActorLocation();
	FVector EndPoint = (AIController->GetPawn()->GetActorForwardVector() * 250.f) + StartPoint;

	//Set Object Type to look for
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectType;
	ObjectType.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));

	//Sets Actor to ignore
	TArray<AActor*> IgnoredActors;
	IgnoredActors.Add(AIController->GetPawn());
	
	TArray<AActor*> FoundAI;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABaseAi::StaticClass(), FoundAI);
	for (int i = 0; i < FoundAI.Num(); i++) {
		IgnoredActors.Add(FoundAI[i]);
	}

	FHitResult OutHit;

	if (UKismetSystemLibrary::SphereTraceSingleForObjects(GetWorld(), StartPoint, EndPoint, Radius, ObjectType, false, IgnoredActors,
		EDrawDebugTrace::None, OutHit, true) && Cast<ABaseCharacter>(OutHit.GetActor())) {
		AI->MeleePlayer(OutHit);

		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return EBTNodeResult::Succeeded;
	}
	else {
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Failing to hit player"));
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return EBTNodeResult::Failed;
	}
}
