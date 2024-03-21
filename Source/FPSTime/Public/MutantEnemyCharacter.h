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
	AMutantEnemyCharacter();

	void NotifyActorBeginOverlap(AActor* OtherActor) override;
	void NotifyActorEndOverlap(AActor* OtherActor) override;

	virtual void Attack() override;
	void Intimidate();

private:
	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* AttackTrigger;

	UPROPERTY(EditAnywhere)
	class UAnimMontage* AttackAnimMontage;

	UPROPERTY(EditAnywhere)
	float Damage;

	class APlayerCharacter* Player;

	bool bPlayerInAttackRange;
};
