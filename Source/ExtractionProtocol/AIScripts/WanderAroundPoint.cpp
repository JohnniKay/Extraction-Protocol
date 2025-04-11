// Fill out your copyright notice in the Description page of Project Settings.

//Created Classes
#include "WanderAroundPoint.h"
#include "BaseAIController.h"
//Unreal Classes
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UWanderAroundPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
	Super::ExecuteTask(OwnerComp, NodeMemory);

	//Get AI Controller
	ABaseAIController* AIController = Cast<ABaseAIController>(OwnerComp.GetAIOwner());

	//Get Nav System
	UNavigationSystemV1* const NavSys = UNavigationSystemV1::GetCurrent(GetWorld());

	//Result Location
	FNavLocation Location;

	if (NavSys->GetRandomPointInNavigableRadius(AIController->GetPawn()->GetActorLocation(), Radius, Location, nullptr)) {
		AIController->GetBlackboardComponent()->SetValueAsVector(TEXT("Destination"), Location.Location);
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return EBTNodeResult::Succeeded;
	}
	else {
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return EBTNodeResult::Failed;
	}
}
