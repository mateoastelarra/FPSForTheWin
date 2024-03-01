// Fill out your copyright notice in the Description page of Project Settings.


#include "KillForKeysGameMode.h"

void AKillForKeysGameMode::PawnKilled(APawn* PawnKilled)
{
	Super::PawnKilled(PawnKilled);
	APlayerController* PlayerController = Cast<APlayerController>(PawnKilled->GetController());
	if (PlayerController)
	{	
		PlayerController->GameHasEnded(nullptr, false);
	}
}

void AKillForKeysGameMode::AddKey()
{
	CurrentKeys++;
}

void AKillForKeysGameMode::LoseKeys(int KeysToLose)
{
	CurrentKeys -= KeysToLose;
}

int AKillForKeysGameMode::GetCurrentKeys()
{
	return CurrentKeys;
}

FString AKillForKeysGameMode::GetCurrentKeysUIText()
{
	return FString::Printf(TEXT("Keys:  %d"), CurrentKeys);
}
