// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Destructible.h"
#include "PlayerCharacter.generated.h"

class AGun;

UCLASS()
class FPSTIME_API APlayerCharacter : public ACharacter, public IDestructible
{
	GENERATED_BODY()

public:
	APlayerCharacter();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void NotifyActorBeginOverlap(AActor* OtherActor) override;

	void AddPistolBullets(int BulletsToAdd, int GunIndex);

	virtual void Destroyed() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UCameraComponent* Cam;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool Walking;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool ShouldHideWeapon;

	

private:
	UPROPERTY(EditAnywhere, Category = "Movement")
	float MovementSpeed = 10.f;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float LookSpeed = 100.f;

	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<AGun>> GunClasses;

	UPROPERTY()
	TArray<AGun*> Guns;

	UPROPERTY(EditAnywhere)
	float ChangeWeaponRate = 1.f;

	UFUNCTION(BluePrintPure)
	AGun* GetCurrentGun();

	UFUNCTION(BluePrintPure)
	int GetCurrentGunAmmo();

	UFUNCTION(BluePrintPure)
	int GetRemainingGunAmmo();

	UPROPERTY(EditAnywhere)
	TArray<class UAnimMontage*> ShootAnimMontages;

	UPROPERTY(EditAnywhere)
	class UAnimMontage* ReloadAnimMontage;

	int CurrentGunIndex = 0;
	FTimerHandle ChangeWeaponTimerHandle;
	float DeltaSeconds;
	bool bIsShooting;
	float ShootingRate;
	FTimerHandle ShootingTimerHandle;

	void MoveForward(float value);
	void MoveRight(float value);
	void LookUp(float value);
	void LookRight(float value);

	void SetGun(int GunIndex);
	void AddGun(int GunIndex);
	void ChangeWeapon();
	void HideWeapon();
	void ShowWeapon();
	void Fire();
	void StartShooting();
	void StopShooting();
	void Reload();
	
};
