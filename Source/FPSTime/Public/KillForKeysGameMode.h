// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FPSTimeGameModeBase.h"
#include "KillForKeysGameMode.generated.h"

/**
 * 
 */
UCLASS()
class FPSTIME_API AKillForKeysGameMode : public AFPSTimeGameModeBase
{
	GENERATED_BODY()

public:
	virtual void PawnKilled(APawn* PawnKilled) override;
};
