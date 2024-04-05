// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSTimePlayerController.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"

void AFPSTimePlayerController::BeginPlay()
{
	Super::BeginPlay();

	FString CurrentLevelName = GetWorld()->GetMapName();

	UE_LOG(LogTemp, Warning, TEXT("%s"), *CurrentLevelName);

	if (CurrentLevelName != "UEDPIE_0_Map1") { return; }
	HUD = CreateWidget(this, HUDClass);
	if (HUD)
	{
		HUD->AddToViewport();
	}

	UUserWidget* PauseScreen = CreateWidget(this, PauseScreenClass);
	if (PauseScreen)
	{
		PauseScreen->AddToViewport();
	}

	if (BackgroundMusic)
	{
		MusicAudioComponent = UGameplayStatics::SpawnSound2D(this, 
															BackgroundMusic, 
															BackgroundMusicVolume, 
															1, 0, nullptr, false, true);
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
	if (MusicAudioComponent)
	{
		MusicAudioComponent->FadeOut(RestartDelay, 0);
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
	if (!IsPaused())
	{
		bPauseScreenVisible = true;
		UGameplayStatics::SetGamePaused(this, true);
	}
	else
	{
		UGameplayStatics::SetGamePaused(this, false);;
		bPauseScreenVisible = false;
	}
}

bool AFPSTimePlayerController::GetbPauseScreenVisible()
{
	return bPauseScreenVisible;
}