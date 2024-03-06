// Fill out your copyright notice in the Description page of Project Settings.


#include "TwoSidesDoorActor.h"
#include "FPSTime/PlayerCharacter.h"
#include "KillForKeysGameMode.h"
#include "Math/Vector.h"
#include "Kismet/GameplayStatics.h"

void ATwoSidesDoorActor::NotifyActorBeginOverlap(AActor* OtherActor)
{
	APlayerCharacter* Player = Cast<APlayerCharacter>(OtherActor);
	if (Player)
	{
		AGameModeBase* AuthGameMode = GetWorld()->GetAuthGameMode();
		AKillForKeysGameMode* CurrentGameMode = Cast<AKillForKeysGameMode>(GetWorld()->GetAuthGameMode());
		if (CurrentGameMode)
		{
			FVector RelativePositionWithPlayer = Player->GetActorLocation() - GetActorLocation();
			float DotProduct = FVector::DotProduct(RelativePositionWithPlayer, ForwardVector);
			if (DotProduct> 0)
			{
				bShouldMove = true;
				PlayerMessage = TEXT("You unlocked it.");
				if (UnlockedSound && OpenSound)
				{
					UGameplayStatics::PlaySoundAtLocation(GetWorld(), UnlockedSound, GetActorLocation());
					UGameplayStatics::PlaySoundAtLocation(GetWorld(), OpenSound, GetActorLocation());
				}
			}
			else
			{
				PlayerMessage = TEXT("It´s locked from the other side.");
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
