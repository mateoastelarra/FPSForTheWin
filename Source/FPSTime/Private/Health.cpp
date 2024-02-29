// Fill out your copyright notice in the Description page of Project Settings.


#include "Health.h"
#include "Destructible.h"

UHealth::UHealth()
{
	PrimaryComponentTick.bCanEverTick = true;

	
}

void UHealth::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;
	CurrentShield = MaxShield;
}

void UHealth::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UHealth::TakeDamage(float Damage)
{
	if (CurrentShield - Damage >= 0)
	{
		CurrentShield -= Damage;
	}
	else
	{
		CurrentHealth += (CurrentShield - Damage);
		if (CurrentHealth <= 0)
		{
			IDestructible* Destructible = Cast<IDestructible>(GetOwner());
			if (Destructible)
			{
				Destructible->Destroyed();
				UE_LOG(LogTemp, Warning, TEXT("Called Destructible method"));
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("Trying to destroy a non destructible object"));
			}
		}
	}
}

void UHealth::AddHealth(int HealthToAdd)
{
	CurrentHealth = FMath::Min(MaxHealth, CurrentHealth + HealthToAdd);
}

void UHealth::AddShield(int ShieldToAdd)
{
	CurrentShield = FMath::Min(MaxShield, CurrentShield + ShieldToAdd);
}

bool UHealth::IsDead() const
{
	return CurrentHealth <= 0;
}
