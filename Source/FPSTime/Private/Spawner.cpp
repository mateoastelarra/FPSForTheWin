// Fill out your copyright notice in the Description page of Project Settings.


#include "Spawner.h"
#include "Components/PrimitiveComponent.h"
#include "Components/BoxComponent.h"
#include "Destructible.h"
#include "FPSTime/PlayerCharacter.h"


ASpawner::ASpawner()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	Trigger->SetupAttachment(Root);
}

void ASpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpawner::NotifyActorBeginOverlap(AActor* OtherActor)
{
	APlayerCharacter* Player = Cast<APlayerCharacter>(OtherActor);
	if (Player && IsActive)
	{
		for (int i = 0; i < AmountOfEnemiesToSpawn; i++)
		{
			SpawnRandomActorInSpawnPoint(i);
		}
		IsActive = false;
	}
}

void ASpawner::SpawnRandomActorInSpawnPoint(int index)
{
	int ActorToSpawnIndex = rand() % ActorsToSpawn.Num();

	TSubclassOf<AActor> ActorToSpawn = ActorsToSpawn[ActorToSpawnIndex];
	FVector SpawnLocation = SpawnPoints[index]->GetActorLocation();

	if (ActorToSpawn == nullptr) { return; }
	AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(ActorToSpawn, SpawnLocation, GetActorRotation());
	IDestructible* SpawnedDestructible = Cast<IDestructible>(SpawnedActor);
	if (SpawnedDestructible)
	{
		SpawnedEnemies.Add(SpawnedDestructible);
		SpawnedDestructible->EnemySpawner = this;
	}	
}

void ASpawner::RemoveFromSpawnedActors(IDestructible* EnemyToRemove)
{
	if (EnemyToRemove == nullptr) { return; }
	SpawnedEnemies.Remove(EnemyToRemove);
	if (SpawnedEnemies.Num() == 0 && KeyToDrop != nullptr)
	{
		TSubclassOf<AActor> ActorToSpawn = KeyToDrop;
		FVector SpawnLocation = KeySpawnPoint->GetActorLocation();
		GetWorld()->SpawnActor<AActor>(ActorToSpawn, SpawnLocation, GetActorRotation());
	}
}

