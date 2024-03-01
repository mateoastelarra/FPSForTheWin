// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSTimePlayerController.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"

void AFPSTimePlayerController::BeginPlay()
{
	Super::BeginPlay();

	HUD = CreateWidget(this, CrossHairClass);
	if (HUD)
	{
		HUD->AddToViewport();
	}
}

void AFPSTimePlayerController::GameHasEnded(AActor* EndGameFocus, bool bIsWinner)
{
	Super::GameHasEnded(EndGameFocus, bIsWinner);

	if (HUD)
	{
		HUD->RemoveFromViewport();
	}

	UUserWidget* DeadScreen = CreateWidget(this, DeadScreenClass);
	if (DeadScreen)
	{
		DeadScreen->AddToViewport();
	}

	GetWorldTimerManager().SetTimer(RestartTimer, this, &APlayerController::RestartLevel, RestartDelay);
}


