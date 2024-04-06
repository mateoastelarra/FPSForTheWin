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

	AActor* GetClipMesh();

private:
	UPROPERTY(VisibleAnywhere)
		USceneComponent* Root;

	UPROPERTY(VisibleAnywhere)
		USkeletalMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
		AActor* Clip;

	UPROPERTY(EditAnywhere, Category  = "FX")
		UParticleSystem* MuzzleFlash;

	UPROPERTY(EditAnywhere, Category = "FX")
		UParticleSystem* ImpactEffect;

	UPROPERTY(EditAnywhere, Category = "Audio")
		USoundBase* FireSound;

	UPROPERTY(EditAnywhere, Category = "Audio")
		USoundBase* EmptySound;

	UPROPERTY(EditAnywhere, Category = "Audio")
		USoundBase* HitSound;

	UPROPERTY(EditAnywhere, Category = "Audio")
		USoundBase* ReloadSound;

	UPROPERTY(EditAnywhere, Category = "UI")
		UTexture2D* ImageWeaponBody;

	UPROPERTY(EditAnywhere, Category = "UI")
		UTexture2D* ImageWeaponMagazine;

	UPROPERTY(EditAnywhere, Category = "Combat")
		float MaxRange = 1000.f;

	UPROPERTY(EditAnywhere, Category = "Combat")
		float Damage = 10;

	UPROPERTY(EditAnywhere, Category = "Combat")
		int StartingBullets = 10;

	UPROPERTY(EditAnywhere, Category = "Combat")
		int BulletsCapacity = 10;

	UPROPERTY(EditAnywhere, Category = "Combat")
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
