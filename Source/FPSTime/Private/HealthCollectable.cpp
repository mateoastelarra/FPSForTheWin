
#include "HealthCollectable.h"
#include "FPSTime/PlayerCharacter.h"

void AHealthCollectable::Use(AActor* User)
{
	APlayerCharacter* Player = Cast<APlayerCharacter>(User);
	if (Player)
	{
		int HealthToAdd = FMath::RandRange(MinHealthToAdd, MaxHealthToAdd);
		Player->AddHealth(HealthToAdd);
		UE_LOG(LogTemp, Warning, TEXT("YUMMY"));
		Destroy();
	}
}
