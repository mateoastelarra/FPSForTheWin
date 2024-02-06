// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Collectable.h"
#include "HealthCollectable.generated.h"

/**
 * 
 */
UCLASS()
class FPSTIME_API AHealthCollectable : public ACollectable
{
	GENERATED_BODY()

public:
	virtual void Use(AActor* User) override;

private:
	UPROPERTY(EditDefaultsOnly)
	int MaxHealthToAdd = 25;

	UPROPERTY(EditDefaultsOnly)
	int MinHealthToAdd = 100;
};
