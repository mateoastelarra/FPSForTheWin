// Fill out your copyright notice in the Description page of Project Settings.


#include "Health.h"

// Sets default values for this component's properties
UHealth::UHealth()
{
	PrimaryComponentTick.bCanEverTick = true;

	
}

void UHealth::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;
}

void UHealth::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UHealth::TakeDamage(float Damage)
{
	CurrentHealth -= Damage;
	if (CurrentHealth <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("ENEMY DEAD"));
	}
}

