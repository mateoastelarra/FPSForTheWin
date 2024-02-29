// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSTimePlayerController.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"

void AFPSTimePlayerController::GameHasEnded(AActor* EndGameFocus, bool bIsWinner)
{
	Super::GameHasEnded(EndGameFocus, bIsWinner);

	UUserWidget* DeadScreen = CreateWidget(this, DeadScreenClass);
	if (DeadScreen)
	{
		DeadScreen->AddToViewport();
	}

	UE_LOG(LogTemp, Warning, TEXT("Game Has Ended"));
	GetWorldTimerManager().SetTimer(RestartTimer, this, &APlayerController::RestartLevel, RestartDelay);
}
