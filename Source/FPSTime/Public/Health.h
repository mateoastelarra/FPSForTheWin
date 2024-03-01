// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Damageable.h"
#include "Health.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FPSTIME_API UHealth : public UActorComponent, public IDamageable
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealth();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	float MaxHealth = 100.f;

	UPROPERTY(EditAnywhere)
	float MaxShield = 0.f;

	UPROPERTY(EditAnywhere)
	float CurrentHealth;

	UPROPERTY(EditAnywhere)
	float CurrentShield;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void TakeDamage(float Damage) override;

	void AddHealth(int HealthToAdd);

	void AddShield(int ShieldToAdd);

	UFUNCTION(BlueprintPure)
	bool IsDead() const;

	UFUNCTION(BlueprintPure)
	float GetHealthPercentage();

	UFUNCTION(BlueprintPure)
	float GetShieldPercentage();
};
