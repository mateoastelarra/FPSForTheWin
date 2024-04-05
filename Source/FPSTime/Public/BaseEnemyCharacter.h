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
	ABaseEnemyCharacter();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<AActor>> CollectablesToSpawn;

	void SpawnCollectableWhenDead();

public:	
	UPROPERTY(EditAnywhere)
		float ChaseRange = 3000.f;

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Attack();

	virtual void Destroyed() override;

};
