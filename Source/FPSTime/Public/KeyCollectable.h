// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Collectable.h"
#include "KeyCollectable.generated.h"

/**
 * 
 */
UCLASS()
class FPSTIME_API AKeyCollectable : public ACollectable
{
	GENERATED_BODY()
	
public:
	virtual void Use(AActor* User) override;
};
