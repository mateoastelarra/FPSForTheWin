// Fill out your copyright notice in the Description page of Project Settings.


#include "Spawner.h"
#include "Components/PrimitiveComponent.h"
#include "Components/BoxComponent.h"
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
	if (Player)
	{
		for (int i = 0; i < AmountOfEnemiesToSpawn; i++)
		{
			SpawnRandomActorInRandomSpawnPoint();
		}
		Destroy();
	}
}

void ASpawner::SpawnRandomActorInRandomSpawnPoint()
{
	int ActorToSpawnIndex = rand() % ActorsToSpawn.Num();
	int SpawnPointIndex = rand() % SpawnPoints.Num();

	TSubclassOf<AActor> ActorToSpawn = ActorsToSpawn[ActorToSpawnIndex];
	FVector SpawnLocation = SpawnPoints[SpawnPointIndex]->GetActorLocation();

	GetWorld()->SpawnActor<AActor>(ActorToSpawn, SpawnLocation, GetActorRotation());
}

