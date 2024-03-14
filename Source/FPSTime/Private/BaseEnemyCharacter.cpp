// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEnemyCharacter.h"
#include "Gun.h"
#include "Components/CapsuleComponent.h"
#include "Spawner.h"
#include "Destructible.h"

// Sets default values
ABaseEnemyCharacter::ABaseEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ABaseEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	Gun = GetWorld()->SpawnActor<AGun>(GunClass);
	GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);
	Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
	Gun->SetOwner(this);
}

// Called every frame
void ABaseEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABaseEnemyCharacter::Shoot()
{
	Gun->PullTrigger();
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
