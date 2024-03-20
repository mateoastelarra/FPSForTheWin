// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEnemyCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Spawner.h"
#include "Destructible.h"

ABaseEnemyCharacter::ABaseEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ABaseEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABaseEnemyCharacter::Attack()
{
	UE_LOG(LogTemp, Warning, TEXT("We Shall Attack"));
}

void ABaseEnemyCharacter::Destroyed()
{
	if (EnemySpawner)
	{
		IDestructible* DestructibleActor = Cast<IDestructible>(this);
		EnemySpawner->RemoveFromSpawnedActors(DestructibleActor);
	}

	SpawnCollectableWhenDead();
	DetachFromControllerPendingDestroy();
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ABaseEnemyCharacter::SpawnCollectableWhenDead()
{
	int CollectableToSpawnIndex = rand() % CollectablesToSpawn.Num();
	TSubclassOf<AActor> CollectableToSpawn = CollectablesToSpawn[CollectableToSpawnIndex];
	FVector SpawnLocation = GetActorLocation();
	GetWorld()->SpawnActor<AActor>(CollectableToSpawn, SpawnLocation, GetActorRotation());
}
