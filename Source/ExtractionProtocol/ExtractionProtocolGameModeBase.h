// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ExtractionProtocolGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class EXTRACTIONPROTOCOL_API AExtractionProtocolGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void Logout(AController* Exiting) override;


	
};
