// Fill out your copyright notice in the Description page of Project Settings.


#include "ShieldCollectable.h"
#include "FPSTime/PlayerCharacter.h"

void AShieldCollectable::Use(AActor* User)
{
	APlayerCharacter* Player = Cast<APlayerCharacter>(User);
	if (Player)
	{
		int ShieldToAdd = FMath::RandRange(MinShieldToAdd, MaxShieldToAdd);
		Player->AddShield(ShieldToAdd);
		UE_LOG(LogTemp, Warning, TEXT("Community Shield"));
		Destroy();
	}
}
