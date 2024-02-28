// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FPSTimePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class FPSTIME_API AFPSTimePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void GameHasEnded(class AActor* EndGameFocus = nullptr, bool bIsWinner = false) override;

private:
	UPROPERTY(EditAnywhere)
	float RestartDelay = 3.f;

	FTimerHandle RestartTimer;
};
