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

	void NotifyActorBeginOverlap(AActor* OtherActor) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UCameraComponent* Cam;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool Walking;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool ShouldHideWeapon;

	void AddHealth(float HealthToAdd);
	void AddShield(float ShieldToAdd);

private:
	UPROPERTY(EditAnywhere, Category = "Combat")
	float MaxHealth = 100.f;
	UPROPERTY(EditAnywhere, Category = "Combat")
	float MaxShield = 100.f;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float MovementSpeed = 10.f;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float LookSpeed = 100.f;

	float CurrentHealth;
	float DeltaSeconds;
	float CurrentShield = 0.f;

	void MoveForward(float value);
	void MoveRight(float value);
	void LookUp(float value);
	void LookRight(float value);

	void SetGun(int GunIndex);
	void AddGun(int GunIndex);
	void HideWeapon();
	void ShowWeapon();
	void Shoot();
	void ChangeWeapon();
	
	void TakeDamage(float Damage);
	
	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<AGun>> GunClasses;

	UPROPERTY()
	TArray<AGun*> Guns;

	UPROPERTY(EditAnywhere)
	float ChangeWeaponRate = 1.f;

	int CurrentGun = 0;
	FTimerHandle ChangeWeaponTimerHandle;
};
