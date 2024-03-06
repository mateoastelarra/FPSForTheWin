// Fill out your copyright notice in the Description page of Project Settings.


#include "KeyDoorActor.h"
#include "FPSTime/PlayerCharacter.h"
#include "KillForKeysGameMode.h"
#include "Kismet/GameplayStatics.h"

void AKeyDoorActor::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	APlayerCharacter* Player = Cast<APlayerCharacter>(OtherActor);
	if (Player)
	{
		AGameModeBase* AuthGameMode = GetWorld()->GetAuthGameMode();
		AKillForKeysGameMode* CurrentGameMode = Cast<AKillForKeysGameMode>(GetWorld()->GetAuthGameMode());
		if (CurrentGameMode)
		{
			int CurrentKeys = CurrentGameMode->GetCurrentKeys();
			if (CurrentKeys >= KeysNeededToOpen)
			{
				bShouldMove = true;
				CurrentGameMode->LoseKeys(KeysNeededToOpen);
				PlayerMessage = TEXT("You used ") + FString::FromInt(KeysNeededToOpen) + TEXT(" keys.");
				if (UnlockedSound && OpenSound)
				{
					UGameplayStatics::PlaySoundAtLocation(GetWorld(), UnlockedSound, GetActorLocation());
					UGameplayStatics::PlaySoundAtLocation(GetWorld(), OpenSound, GetActorLocation());
				}
			}
			else if (!bShouldMove)
			{
				PlayerMessage = TEXT("You need ") + FString::FromInt(KeysNeededToOpen) + TEXT(" keys to open this door.");
				if (LockedSound)
				{
					UGameplayStatics::PlaySoundAtLocation(GetWorld(), LockedSound, GetActorLocation());
				}
			}
			CurrentGameMode->SetPlayerMessage(PlayerMessage);
			CurrentGameMode->SetPlayerMessageUIVisibility(true);
		}
	}
}
