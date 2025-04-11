// Fill out your copyright notice in the Description page of Project Settings.


#include "Base_TempEndGameScenarioObject.h"

// Sets default values
ABase_TempEndGameScenarioObject::ABase_TempEndGameScenarioObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABase_TempEndGameScenarioObject::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABase_TempEndGameScenarioObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

