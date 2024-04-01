// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "HealthCollectable.h"
#include "Kismet/GameplayStatics.h"
#include "Gun.h"
#include "FPSTimeGameModeBase.h"
#include "Components/CapsuleComponent.h"
#include "Animation/AnimInstance.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	Cam = CreateDefaultSubobject<UCameraComponent>("Camera");
	Cam->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	CurrentGunIndex = 0;
	for (int i = 0; i < GunClasses.Num(); i++)
	{
		AddGun(i);
	}
	SetGun(CurrentGunIndex);
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DeltaSeconds = DeltaTime;

	Walking = GetVelocity().Size() > 0;
}

void APlayerCharacter::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	ACollectable* Consumable = Cast<ACollectable>(OtherActor);
	if (Consumable)
	{
		Consumable->Use(this);
	}
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &APlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APlayerCharacter::LookUp);
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &APlayerCharacter::LookRight);
	PlayerInputComponent->BindAction(TEXT("StartShooting"), IE_Pressed, this, &APlayerCharacter::StartShooting);
	PlayerInputComponent->BindAction(TEXT("StopShooting"), IE_Released, this, &APlayerCharacter::StopShooting);
	PlayerInputComponent->BindAction(TEXT("ChangeWeapon"), IE_Pressed, this, &APlayerCharacter::ChangeWeapon);
	PlayerInputComponent->BindAction(TEXT("Reload"), IE_Pressed, this, &APlayerCharacter::Reload);
}

void APlayerCharacter::MoveForward(float value)
{
	FVector MovementVector = GetActorForwardVector() * MovementSpeed * value * DeltaSeconds;
	AddMovementInput(MovementVector);
}

void APlayerCharacter::MoveRight(float value)
{
	FVector MovementVector = GetActorRightVector() * MovementSpeed * value * DeltaSeconds;
	AddMovementInput(MovementVector);
}

void APlayerCharacter::LookUp(float value)
{
	AddControllerPitchInput(LookSpeed * value * DeltaSeconds);
}

void APlayerCharacter::LookRight(float value)
{
	AddControllerYawInput(LookSpeed * value * DeltaSeconds);
}

void APlayerCharacter::StartShooting()
{
	bIsShooting = true;
	ShootingRate = Guns[CurrentGunIndex]->GetShootingRate();
	GetWorldTimerManager().SetTimer(ShootingTimerHandle, this, &APlayerCharacter::Fire, ShootingRate, true, 0);
}

void APlayerCharacter::StopShooting()
{
	bIsShooting = false;
	GetWorldTimerManager().ClearTimer(ShootingTimerHandle);
}

void APlayerCharacter::Fire()
{
	if (GetCurrentGunAmmo() <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("NO BULLETS"));
		Guns[CurrentGunIndex]->PullTrigger();
		StopShooting();
		return;
	}
	if (bIsShooting)
	{
		UAnimInstance* PlayerAnimInstance = GetMesh()->GetAnimInstance();
		if (PlayerAnimInstance && ShootAnimMontages[CurrentGunIndex])
		{
			UE_LOG(LogTemp, Warning, TEXT("Before playing montage: %d"), CurrentGunIndex);
			PlayerAnimInstance->Montage_Play(ShootAnimMontages[CurrentGunIndex]);
			UE_LOG(LogTemp, Warning, TEXT("After playing montage"));
		}
		Guns[CurrentGunIndex]->PullTrigger();
	}
}

void APlayerCharacter::Reload()
{
	Guns[CurrentGunIndex]->Reload();
	UAnimInstance* PlayerAnimInstance = GetMesh()->GetAnimInstance();
	if (PlayerAnimInstance && ReloadAnimMontages[CurrentGunIndex])
	{
		PlayerAnimInstance->Montage_Play(ReloadAnimMontages[CurrentGunIndex]);
	}
}

void APlayerCharacter::SetGun(int GunIndex)
{
	if (Guns[GunIndex])
	{
		Guns[GunIndex]->SetActorHiddenInGame(false);
		Guns[GunIndex]->SetActorEnableCollision(true);
	}
	Guns[GunIndex]->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("SOCKET_Weapon_L"));
	Guns[GunIndex]->SetOwner(this);
}

void APlayerCharacter::ChangeWeapon()
{
	ShouldHideWeapon = true;
	GetWorld()->GetTimerManager().SetTimer(ChangeWeaponTimerHandle, this, &APlayerCharacter::ShowWeapon, ChangeWeaponRate, false);
}

void APlayerCharacter::ShowWeapon()
{
	HideWeapon();
	CurrentGunIndex = (CurrentGunIndex + 1) % GunClasses.Num();
	SetGun(CurrentGunIndex);
}

void APlayerCharacter::HideWeapon()
{
	ShouldHideWeapon = false;
	if (Guns[CurrentGunIndex])
	{
		Guns[CurrentGunIndex]->SetActorHiddenInGame(true);
		Guns[CurrentGunIndex]->SetActorEnableCollision(false);
	}
}

void APlayerCharacter::AddGun(int GunIndex)
{
	Guns.Add(GetWorld()->SpawnActor<AGun>(GunClasses[GunIndex]));
	if (Guns[GunIndex])
	{
		Guns[GunIndex]->SetActorHiddenInGame(true);
		Guns[GunIndex]->SetActorEnableCollision(false);
	}
}

void APlayerCharacter::AddPistolBullets(int GunIndex, int BulletsToAdd)
{
	Guns[GunIndex]->AddBullets(BulletsToAdd);
}

void APlayerCharacter::Destroyed()
{	
	AFPSTimeGameModeBase* GameMode = GetWorld()->GetAuthGameMode<AFPSTimeGameModeBase>();
	if (GameMode)
	{
		GameMode->PawnKilled(this);
	}
	StopShooting();
	HideWeapon();
	GetMesh()->DestroyComponent();
	DetachFromControllerPendingDestroy();
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

AGun* APlayerCharacter::GetCurrentGun()
{
	return Guns[CurrentGunIndex];
}

int APlayerCharacter::GetCurrentGunAmmo()
{
	return Guns[CurrentGunIndex]->GetCurrentBullets();
}

int APlayerCharacter::GetRemainingGunAmmo()
{
	return Guns[CurrentGunIndex]->GetRemainingAmmo();
}
