// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

class AGun;

UCLASS()
class FPSTIME_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UCameraComponent* Cam;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool Walking;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool ShouldChangeWeapon;

private:
	UPROPERTY(EditAnywhere, Category = "Combat")
	float MaxHealth = 100.f;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float MovementSpeed = 10.f;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float LookSpeed = 100.f;

	float CurrentHealth;
	float DeltaSeconds;

	void MoveForward(float value);
	void MoveRight(float value);
	void LookUp(float value);
	void LookRight(float value);

	void SetGun(int GunIndex);
	void Shoot();
	void ChangeWeapon();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AGun> GunClass;

	UPROPERTY()
	TArray<AGun*> Guns;

	int CurrentGun = 0;
};
