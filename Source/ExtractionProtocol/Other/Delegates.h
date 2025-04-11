// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Delegates.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEventDispatcher);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FHealthChange, float, CurrentHealth, float, MaxHealth);
/**
 * 
 */
UCLASS()
class EXTRACTIONPROTOCOL_API UDelegates : public UObject
{
	GENERATED_BODY()
	
};
