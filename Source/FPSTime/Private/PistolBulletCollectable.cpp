// Fill out your copyright notice in the Description page of Project Settings.


#include "PistolBulletCollectable.h"
#include "FPSTime/PlayerCharacter.h"

void APistolBulletCollectable::Use(AActor* User)
{
	APlayerCharacter* Player = Cast<APlayerCharacter>(User);
	if (Player)
	{
		int BulletsToAdd = FMath::RandRange(MinBulletsToAdd, MaxBulletsToAdd);
		Player->AddPistolBullets(IsPistol, BulletsToAdd);
		UE_LOG(LogTemp, Warning, TEXT("More Bullets"));
		Destroy();
	}
}
