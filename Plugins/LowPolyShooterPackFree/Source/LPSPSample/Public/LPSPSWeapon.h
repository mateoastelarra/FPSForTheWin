// Copyright 2021, Infima Games. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LPSPSWeapon.generated.h"

//Base Weapon Class.
UCLASS(Abstract)
class LPSPSAMPLE_API ALPSPSWeapon final : public AActor
{
	GENERATED_BODY()

public:
	//Constructor.
	ALPSPSWeapon();
protected:
	//Should this Weapon be automatic?
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Low Poly Shooter Pack Sample | Weapon | Settings")
	bool bAutomatic;

	//Amount of rounds per minute that the Weapon can fire.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Low Poly Shooter Pack Sample | Weapon | Settings")
	float RateOfFire;

	//Maximum ammunition that the Weapon's magazine can hold.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Low Poly Shooter Pack Sample | Weapon | Settings")
	int AmmunitionMax;

	//Firing Montage.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Low Poly Shooter Pack Sample | Weapon | Animation")
	UAnimMontage* MontageFire;

	//Reload Montage.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Low Poly Shooter Pack Sample | Weapon | Animation")
	UAnimMontage* MontageReload;

	//Reload Empty Montage. Played when reloading without any leftover ammunition.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Low Poly Shooter Pack Sample | Weapon | Animation")
	UAnimMontage* MontageReloadEmpty;

	//Texture displayed in the player's heads up display to represent this Weapon's shape/body.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Low Poly Shooter Pack Sample | Weapon | Display")
	UTexture* TextureWeaponBody;

	//Texture displayed in the player's heads up display to represent this Weapon's magazine.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Low Poly Shooter Pack Sample | Weapon | Display")
	UTexture* TextureWeaponMagazine;

	//Texture displayed in the player's heads up display to represent this Weapon's ironsights.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Low Poly Shooter Pack Sample | Weapon | Display")
	UTexture* TextureWeaponIronsights;
	
	//Result from hitting something when firing.
	UPROPERTY(BlueprintReadWrite, Category = "Low Poly Shooter Pack Sample | Data")
	FHitResult HitResult;

	//Current amount of bullets in the magazine.
	UPROPERTY(BlueprintReadWrite, Category = "Low Poly Shooter Pack Sample | Data")
	int AmmunitionCurrent;
};