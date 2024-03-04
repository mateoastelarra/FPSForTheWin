// Fill out your copyright notice in the Description page of Project Settings.


#include "PistolBulletCollectable.h"
#include "FPSTime/PlayerCharacter.h"
#include "Engine/Engine.h"

void APistolBulletCollectable::Use(AActor* User)
{
	Super::Use(User);

	APlayerCharacter* Player = Cast<APlayerCharacter>(User);
	if (Player)
	{
		int BulletsToAdd = FMath::RandRange(MinBulletsToAdd, MaxBulletsToAdd);
		Player->AddPistolBullets(IsPistol, BulletsToAdd);
		Destroy();
	}
}
