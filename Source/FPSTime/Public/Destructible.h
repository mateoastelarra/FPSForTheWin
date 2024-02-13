// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Destructible.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UDestructible : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class FPSTIME_API IDestructible
{
	GENERATED_BODY()

public:
	virtual void Destroyed() = 0;
};
