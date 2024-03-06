// Fill out your copyright notice in the Description page of Project Settings.


#include "TwoSidesDoorActor.h"
#include "FPSTime/PlayerCharacter.h"
#include "KillForKeysGameMode.h"

void ATwoSidesDoorActor::NotifyActorBeginOverlap(AActor* OtherActor)
{
	APlayerCharacter* Player = Cast<APlayerCharacter>(OtherActor);
	if (Player)
	{
		AGameModeBase* AuthGameMode = GetWorld()->GetAuthGameMode();
		AKillForKeysGameMode* CurrentGameMode = Cast<AKillForKeysGameMode>(GetWorld()->GetAuthGameMode());
		if (CurrentGameMode)
		{
			FVector RelativePositionWithPlayer = GetActorLocation() - Player->GetActorLocation();
			if (RelativePositionWithPlayer.X > 0)
			{
				bShouldMove = true;
				
				PlayerMessage = TEXT("Pass");
			}
			else
			{
				PlayerMessage = TEXT("Dont Pass");
			}
			CurrentGameMode->SetPlayerMessage(PlayerMessage);
			CurrentGameMode->SetPlayerMessageUIVisibility(true);
		}
	}
}
