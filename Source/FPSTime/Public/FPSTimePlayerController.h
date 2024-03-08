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

	void SetCollectableName(FString Name);

	void SetCollectableUIVisible();

protected:
	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> DeadScreenClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> HUDClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> PauseScreenClass;

	UPROPERTY(EditAnywhere)
	float RestartDelay = 3.f;

	UPROPERTY(EditAnywhere)
	float CollectableUIDelay = 2.f;

	UPROPERTY(EditAnywhere)
	USoundBase* BackgroundMusic;

	UPROPERTY(EditAnywhere)
	float BackgroundMusicVolume = 1.f;

	UPROPERTY()
	UUserWidget* HUD;

	FTimerHandle RestartTimer;

	FTimerHandle CollectableUITimer;

	FString CollectableName;

	bool bCollectableUIVisible = false;

	bool bPauseScreenVisible = false;

	UAudioComponent* MusicAudioComponent;

	UFUNCTION(BlueprintPure)
	FString GetCurrentCollectableUIText();

	UFUNCTION(BluePrintPure)
	ESlateVisibility SetTextVisibility(bool bIsVisible);

	UFUNCTION(BluePrintPure)
	bool GetbCollectableUIVisible();

	UFUNCTION(BluePrintPure)
	bool GetbPauseScreenVisible();

	void SetCollectableUIInvisible();

	void PauseGame();

};
