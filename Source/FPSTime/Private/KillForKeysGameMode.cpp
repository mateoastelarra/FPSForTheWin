// Fill out your copyright notice in the Description page of Project Settings.


#include "KillForKeysGameMode.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

void AKillForKeysGameMode::BeginPlay()
{
	Super::BeginPlay();

}

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

void AKillForKeysGameMode::SetPlayerMessageUIVisibility(bool bIsVisible)
{
	bPlayerMessageUIVisible = bIsVisible;
}

void AKillForKeysGameMode::SetPlayerMessage(FString Message)
{
	PlayerMessageUI = Message;
}

bool AKillForKeysGameMode::GetPlayerMessageUIVisibility()
{
	return bPlayerMessageUIVisible;
}

FString AKillForKeysGameMode::GetCurrentKeysUIText()
{
	return FString::Printf(TEXT("Keys:  %d"), CurrentKeys);
}

FString AKillForKeysGameMode::GetPlayerMessageUIText()
{
	return FString::Printf(TEXT("%s"), *PlayerMessageUI);
}

ESlateVisibility AKillForKeysGameMode::SetTextVisibility(bool bIsVisible)
{
	if (bIsVisible)
	{
		return ESlateVisibility::Visible;
	}
	return ESlateVisibility::Hidden;
}
