// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Spawner.generated.h"

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

	void SpawnRandomActorInSpawnPoint(int index);
};
