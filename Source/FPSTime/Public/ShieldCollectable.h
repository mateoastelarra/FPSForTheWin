// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Collectable.h"
#include "ShieldCollectable.generated.h"

/**
 * 
 */
UCLASS()
class FPSTIME_API AShieldCollectable : public ACollectable
{
	GENERATED_BODY()

public:
	virtual void Use(AActor* User) override;

private:
	UPROPERTY(EditAnywhere)
	int MaxShieldToAdd = 10;

	UPROPERTY(EditAnywhere)
	int MinShieldToAdd = 100;

};
