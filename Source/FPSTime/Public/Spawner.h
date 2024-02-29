// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Spawner.generated.h"

class IDestructible;

UCLASS()
class FPSTIME_API ASpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	ASpawner();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	void NotifyActorBeginOverlap(AActor* OtherActor) override;

	void RemoveFromSpawnedActors(IDestructible* EnemyToRemove);

private:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* Trigger;

	UPROPERTY(EditAnywhere)
	TArray<AActor*> SpawnPoints;

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<AActor>> ActorsToSpawn;

	UPROPERTY(EditAnywhere)
	int AmountOfEnemiesToSpawn;

	bool IsActive = true;

	TArray<IDestructible*> SpawnedEnemies;

	void SpawnRandomActorInSpawnPoint(int index);
};
