// Fill out your copyright notice in the Description page of Project Settings.


#include "KillForKeysGameMode.h"

void AKillForKeysGameMode::PawnKilled(APawn* PawnKilled)
{
	Super::PawnKilled(PawnKilled);
	UE_LOG(LogTemp, Warning, TEXT("Killed"));
	APlayerController* PlayerController = Cast<APlayerController>(PawnKilled->GetController());
	if (PlayerController)
	{	
		PlayerController->GameHasEnded(nullptr, false);
	}
}
