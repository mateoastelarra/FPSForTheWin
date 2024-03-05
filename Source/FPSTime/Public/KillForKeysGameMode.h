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

	void AddKey();

	void LoseKeys(int KeysToLose);

	int GetCurrentKeys();

	void SetPlayerMessageUIVisibility(bool bIsVisible);

	void SetPlayerMessage(FString Message);

private:
	int CurrentKeys = 0;

	bool bPlayerMessageUIVisible = false;

	FString PlayerMessageUI;

	UFUNCTION(BluePrintPure)
	ESlateVisibility SetTextVisibility(bool bIsVisible);

	UFUNCTION(BlueprintPure)
	FString GetCurrentKeysUIText();

	UFUNCTION(BlueprintPure)
	FString GetPlayerMessageUIText();

	UFUNCTION(BlueprintPure)
	bool GetPlayerMessageUIVisibility();
};
