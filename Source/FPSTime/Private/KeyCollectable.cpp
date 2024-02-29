// Fill out your copyright notice in the Description page of Project Settings.


#include "KeyCollectable.h"
#include "KillForKeysGameMode.h"

void AKeyCollectable::Use(AActor* User)
{
	Super::Use(User);

	AGameModeBase* AuthGameMode = GetWorld()->GetAuthGameMode();
	AKillForKeysGameMode* CurrentGameMode = Cast<AKillForKeysGameMode>(GetWorld()->GetAuthGameMode());
	if (CurrentGameMode)
	{
		CurrentGameMode->AddKey();
	}

	Destroy();
}
