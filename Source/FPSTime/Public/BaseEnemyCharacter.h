// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Destructible.h"
#include "BaseEnemyCharacter.generated.h"

class AGun;

UCLASS()
class FPSTIME_API ABaseEnemyCharacter : public ACharacter, public IDestructible
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseEnemyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AGun> GunClass;

	UPROPERTY()
	AGun* Gun;

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<AActor>> CollectablesToSpawn;

	void SpawnCollectableWhenDead();

public:	
	UPROPERTY(EditAnywhere)
	float ChaseRange = 3000.f;

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Shoot();

	virtual void Destroyed() override;

};
