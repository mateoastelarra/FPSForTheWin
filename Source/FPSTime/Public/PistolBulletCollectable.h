// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Collectable.h"
#include "PistolBulletCollectable.generated.h"

/**
 * 
 */
UCLASS()
class FPSTIME_API APistolBulletCollectable : public ACollectable
{
	GENERATED_BODY()
	
public:
	virtual void Use(AActor* User) override;

private:
	UPROPERTY(EditAnywhere)
	bool IsPistol = true;

	UPROPERTY(EditAnywhere)
	int MinBulletsToAdd = 4;

	UPROPERTY(EditAnywhere)
	int MaxBulletsToAdd = 12;
};
