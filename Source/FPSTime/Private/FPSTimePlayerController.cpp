// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSTimePlayerController.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

void AFPSTimePlayerController::BeginPlay()
{
	Super::BeginPlay();

	HUD = CreateWidget(this, CrossHairClass);
	if (HUD)
	{
		HUD->AddToViewport();
	}
}

void AFPSTimePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	FInputActionBinding& PauseAction = InputComponent->BindAction("Pause", IE_Pressed, this, &AFPSTimePlayerController::PauseGame);
	PauseAction.bExecuteWhenPaused = true;
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

void AFPSTimePlayerController::SetCollectableName(FString Name)
{
	CollectableName = Name;
}

FString AFPSTimePlayerController::GetCurrentCollectableUIText()
{
	return FString::Printf(TEXT("%s Pickup"), *CollectableName);
}

ESlateVisibility AFPSTimePlayerController::SetTextVisibility(bool bIsVisible)
{
	if (bIsVisible)
	{
		return ESlateVisibility::Visible;
	}
	return ESlateVisibility::Hidden;
}

void AFPSTimePlayerController::SetCollectableUIVisible()
{
	bCollectableUIVisible = true;
	GetWorldTimerManager().SetTimer(
		CollectableUITimer, 
		this, 
		&AFPSTimePlayerController::SetCollectableUIInvisible,
		CollectableUIDelay);
}

bool AFPSTimePlayerController::GetbCollectableUIVisible()
{
	return bCollectableUIVisible;
}

void AFPSTimePlayerController::SetCollectableUIInvisible()
{
	bCollectableUIVisible = false;
}

void AFPSTimePlayerController::PauseGame()
{
	UE_LOG(LogTemp, Warning, TEXT("IN PAUSE METHOD"));
	if (!IsPaused())
	{
		UGameplayStatics::SetGamePaused(this, true);
		UE_LOG(LogTemp, Warning, TEXT("Pausing"));
	}
	else
	{
		UGameplayStatics::SetGamePaused(this, false);;
		UE_LOG(LogTemp, Warning, TEXT("UnPausing"));
	}
}
