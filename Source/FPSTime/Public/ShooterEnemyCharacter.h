// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseEnemyCharacter.h"
#include "ShooterEnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class FPSTIME_API AShooterEnemyCharacter : public ABaseEnemyCharacter
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AGun> GunClass;

	UPROPERTY()
	AGun* Gun;

public:
	virtual void Attack() override;
};
