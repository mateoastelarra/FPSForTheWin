// Copyright 2021, Infima Games. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Sound/SoundCue.h"
#include "GameFramework/Character.h"
#include "LPSPSCharacter.generated.h"

//Base Character Class.
UCLASS(Abstract)
class LPSPSAMPLE_API ALPSPSCharacter final : public ACharacter
{
	GENERATED_BODY()

public:
	//Constructor.
	ALPSPSCharacter();
protected:
	//Sound Cue played when this character aims their weapon. This can just be left empty for games that do not need an aiming sound.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Low Poly Shooter Pack Sample | Character | Audio")
	USoundCue* SoundCueAim;

	//Sound Cue played when this character jumps. It only plays once, as soon as the character leaves the ground.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Low Poly Shooter Pack Sample | Character | Audio")
	USoundCue* SoundCueJump;

	//Maximum speed at which the character can move when walking. This value may be modified by a myriad of other values in this blueprint based on the situation, like the sideways and backward movement multipliers.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Low Poly Shooter Pack Sample | Character | Movement Settings")
	float SpeedWalking = 400.0f;

	//Maximum speed at which this character can move when running.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Low Poly Shooter Pack Sample | Character | Movement Settings")
	float SpeedRunning = 700.0f;

	//Maximum speed at which the character can move when walking and aiming their weapon.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Low Poly Shooter Pack Sample | Character | Movement Settings")
	float SpeedAiming = 350.0f;

	//Montage played when the character fires their weapon.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Low Poly Shooter Pack Sample | Character | Animation")
	UAnimMontage* MontageFire;

	//Montage played when the character inspects a weapon.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Low Poly Shooter Pack Sample | Character | Animation")
	UAnimMontage* MontageInspect;

	//Montage played when the character reloads.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Low Poly Shooter Pack Sample | Character | Animation")
	UAnimMontage* MontageReload;

	//Montage played when the character reloads while having no ammo in their weapon's magazine.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Low Poly Shooter Pack Sample | Character | Animation")
	UAnimMontage* MontageReloadEmpty;

	//Animation Montage played when trying to holster the character's weapon.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Low Poly Shooter Pack Sample | Character | Animation")
	UAnimMontage* MontageHolster;

	//Animation Montage played when the character is unholstering their weapon.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Low Poly Shooter Pack Sample | Character | Animation")
	UAnimMontage* MontageUnholster;

	//Offset from the top of the character's capsule at which the first-person will be located.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Low Poly Shooter Pack Sample | Character | View")
	FVector ViewOffset = FVector(0.0f, 0.0f, -35.0f);

	//Type of Weapon used by this Character. Will determine what Weapon is spawned when starting to play this Character.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Low Poly Shooter Pack Sample | Character | Settings")
	TSubclassOf<AActor> ClassWeapon;
	
	//If true, the Character's Weapon is holstered.
	UPROPERTY(BlueprintReadWrite, Category = "Low Poly Shooter Pack Sample | Data")
	bool bHolstered;

	//If true, the Character is aiming.
	UPROPERTY(BlueprintReadWrite, Category = "Low Poly Shooter Pack Sample | Data")
	bool bAiming;

	//If true, the Character is jumping.
	UPROPERTY(BlueprintReadWrite, Category = "Low Poly Shooter Pack Sample | Data")
	bool bJumping;

	//If true, the Character is running.
	UPROPERTY(BlueprintReadWrite, Category = "Low Poly Shooter Pack Sample | Data")
	bool bRunning;

	//Returns true if the player is currently holding the run key.
	UPROPERTY(BlueprintReadWrite, Category = "Low Poly Shooter Pack Sample | Data")
	bool bHoldingKeyRun;

	//Returns true if the player is currently holding the aim key.
	UPROPERTY(BlueprintReadWrite, Category = "Low Poly Shooter Pack Sample | Data")
	bool bHoldingKeyAim;

	//Returns true if the player is currently holding the fire key.
	UPROPERTY(BlueprintReadWrite, Category = "Low Poly Shooter Pack Sample | Data")
	bool bHoldingKeyFire;

	//Returns true if the player is currently holding the crouch key.
	UPROPERTY(BlueprintReadWrite, Category = "Low Poly Shooter Pack Sample | Data")
	bool bHoldingKeyCrouch;

	//Returns true if the player is currently holding the jump key.
	UPROPERTY(BlueprintReadWrite, Category = "Low Poly Shooter Pack Sample | Data")
	bool bHoldingKeyJump;

	//Returns true if the player is currently holding the tutorial key.
	UPROPERTY(BlueprintReadWrite, Category = "Low Poly Shooter Pack Sample | Data")
	bool bHoldingKeyTutorial;

	//Returns true if this Character is currently in the middle of playing the Inspect Montage.
	UPROPERTY(BlueprintReadWrite, Category = "Low Poly Shooter Pack Sample | Data")
	bool bPlayingMontageInspecting;

	//Returns true if this Character is currently in the middle of playing a Reload Montage.
	UPROPERTY(BlueprintReadWrite, Category = "Low Poly Shooter Pack Sample | Data")
	bool bPlayingMontageReloading;

	//Returns true if this Character is currently in the middle of playing a Holster Montage.
	UPROPERTY(BlueprintReadWrite, Category = "Low Poly Shooter Pack Sample | Data")
	bool bPlayingMontageHolstering;

	//Weapon Actor.
	UPROPERTY(BlueprintReadWrite, Category = "Low Poly Shooter Pack Sample | Data")
	AActor* ActorWeapon;

	//Returns the time at which the Character last fired a Weapon.
	UPROPERTY(BlueprintReadWrite, Category = "Low Poly Shooter Pack Sample | Data")
	float LastFireTime;

	//Pitch Input.
	UPROPERTY(BlueprintReadWrite, Category = "Low Poly Shooter Pack Sample | Data")
	float Pitch;

	//Yaw Input.
	UPROPERTY(BlueprintReadWrite, Category = "Low Poly Shooter Pack Sample | Data")
	float Yaw;

	//Horizontal Input.
	UPROPERTY(BlueprintReadWrite, Category = "Low Poly Shooter Pack Sample | Data")
	float Horizontal;

	//Vertical Input.
	UPROPERTY(BlueprintReadWrite, Category = "Low Poly Shooter Pack Sample | Data")
	float Vertical;

	//Is the Weapon's ammunition empty?
	UPROPERTY(BlueprintReadWrite, Category = "Low Poly Shooter Pack Sample | Data")
	bool bIsWeaponEmpty;

	//Weapon Rate Of Fire.
	UPROPERTY(BlueprintReadWrite, Category = "Low Poly Shooter Pack Sample | Data")
	float RateOfFire;
};