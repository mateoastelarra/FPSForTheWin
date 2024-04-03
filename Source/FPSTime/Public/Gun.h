// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

UCLASS()
class FPSTIME_API AGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGun();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void PullTrigger();

	void AddBullets(int BulletsToAdd);

	int GetCurrentBullets();

	int GetRemainingAmmo();

	float GetShootingRate();

	void Reload();

	UStaticMeshComponent* GetClipMesh();

private:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* Clip;

	UPROPERTY(EditAnywhere)
	UParticleSystem* MuzzleFlash;

	UPROPERTY(EditAnywhere)
	UParticleSystem* ImpactEffect;

	UPROPERTY(EditAnywhere)
	USoundBase* FireSound;

	UPROPERTY(EditAnywhere)
	USoundBase* EmptySound;

	UPROPERTY(EditAnywhere)
	USoundBase* HitSound;

	UPROPERTY(EditAnywhere)
	USoundBase* ReloadSound;

	UPROPERTY(EditAnywhere)
	UTexture2D* ImageWeaponBody;

	UPROPERTY(EditAnywhere)
	UTexture2D* ImageWeaponMagazine;

	UPROPERTY(EditAnywhere)
	float MaxRange = 1000.f;

	UPROPERTY(EditAnywhere)
	float Damage = 10;

	UPROPERTY(EditAnywhere)
	int StartingBullets = 10;

	UPROPERTY(EditAnywhere)
	int BulletsCapacity = 10;

	UPROPERTY(EditAnywhere)
	float ShootingRate = 1000;

	UFUNCTION(BluePrintPure)
	UTexture2D* GetImageWeaponBody();

	UFUNCTION(BluePrintPure)
	UTexture2D* GetImageWeaponMagazine();

	UFUNCTION(BluePrintPure)
	int GetCurrentGunAmmo();

	int CurrentLoadedBullets;

	int RemainingBullets;

	bool GunTrace(FHitResult& Hit, FVector& ShotDirection);
};
