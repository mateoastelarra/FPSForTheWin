// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseEnemyCharacter.h"
#include "MutantEnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class FPSTIME_API AMutantEnemyCharacter : public ABaseEnemyCharacter
{
	GENERATED_BODY()

public:
	virtual void Attack() override;
	void Intimidate();
};
