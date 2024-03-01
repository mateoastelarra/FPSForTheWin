// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FPSTimePlayerController.generated.h"

/**
 * 
 */
class UUserWidget;

UCLASS()
class FPSTIME_API AFPSTimePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void GameHasEnded(class AActor* EndGameFocus = nullptr, bool bIsWinner = false) override;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> DeadScreenClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> CrossHairClass;

	UPROPERTY(EditAnywhere)
	float RestartDelay = 3.f;

	UPROPERTY()
	UUserWidget* HUD;

	FTimerHandle RestartTimer;
};
