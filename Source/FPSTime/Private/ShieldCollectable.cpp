// Fill out your copyright notice in the Description page of Project Settings.


#include "ShieldCollectable.h"
#include "Health.h"
#include "FPSTime/PlayerCharacter.h"
#include "Engine/Engine.h"

void AShieldCollectable::Use(AActor* User)
{
	Super::Use(User);

	APlayerCharacter* Player = Cast<APlayerCharacter>(User);
	if (Player)
	{
		int ShieldToAdd = FMath::RandRange(MinShieldToAdd, MaxShieldToAdd);
		UHealth* PlayerHealth = Player->FindComponentByClass<UHealth>();
		if (PlayerHealth)
		{
			PlayerHealth->AddShield(ShieldToAdd);
			Destroy();
		}
	}
}
