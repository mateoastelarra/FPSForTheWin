
#include "HealthCollectable.h"
#include "Health.h"
#include "FPSTime/PlayerCharacter.h"
#include "Engine/Engine.h"

void AHealthCollectable::Use(AActor* User)
{
	Super::Use(User);

	APlayerCharacter* Player = Cast<APlayerCharacter>(User);
	if (Player)
	{
		int HealthToAdd = FMath::RandRange(MinHealthToAdd, MaxHealthToAdd);
		UHealth* PlayerHealth = Player->FindComponentByClass<UHealth>();
		if (PlayerHealth)
		{
			PlayerHealth->AddHealth(HealthToAdd);
			Destroy();
		}	
	}
}
