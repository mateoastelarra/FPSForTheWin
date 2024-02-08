// Fill out your copyright notice in the Description page of Project Settings.


#include "ShieldCollectable.h"
#include "Health.h"
#include "FPSTime/PlayerCharacter.h"

void AShieldCollectable::Use(AActor* User)
{
	APlayerCharacter* Player = Cast<APlayerCharacter>(User);
	if (Player)
	{
		int ShieldToAdd = FMath::RandRange(MinShieldToAdd, MaxShieldToAdd);
		UHealth* PlayerHealth = Player->FindComponentByClass<UHealth>();
		if (PlayerHealth)
		{
			PlayerHealth->AddShield(ShieldToAdd);
			UE_LOG(LogTemp, Warning, TEXT("Community Shield"));
			Destroy();
		}
	}
}
