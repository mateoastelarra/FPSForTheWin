// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Gun.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Cam = CreateDefaultSubobject<UCameraComponent>("Camera");
	Cam->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;
	CurrentGun = 0;
	for (int i = 0; i < GunClasses.Num(); i++)
	{
		AddGun(i);
	}
	SetGun(CurrentGun);
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DeltaSeconds = DeltaTime;

	Walking = GetVelocity().Size() > 0;
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &APlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APlayerCharacter::LookUp);
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &APlayerCharacter::LookRight);
	PlayerInputComponent->BindAction(TEXT("Shoot"), IE_Pressed, this, &APlayerCharacter::Shoot);
	PlayerInputComponent->BindAction(TEXT("ChangeWeapon"), IE_Pressed, this, &APlayerCharacter::ChangeWeapon);
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

void APlayerCharacter::Shoot()
{
	Guns[CurrentGun]->PullTrigger();
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

void APlayerCharacter::TakeDamage(float Damage)
{
	if (CurrentShield - Damage >= 0)
	{
		CurrentShield -= Damage;
	}
	else
	{
		CurrentHealth += (CurrentShield - Damage);
		if (CurrentHealth <= 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("SURPRISE, YOU ARE DEAD!!"));
		}
	}
}

void APlayerCharacter::ShowWeapon()
{
	HideWeapon();
	CurrentGun = (CurrentGun + 1) % GunClasses.Num();
	SetGun(CurrentGun);
}

void APlayerCharacter::HideWeapon()
{
	ShouldHideWeapon = false;
	if (Guns[CurrentGun])
	{
		UE_LOG(LogTemp, Warning, TEXT("HIDE WEAPON"));
		Guns[CurrentGun]->SetActorHiddenInGame(true);
		Guns[CurrentGun]->SetActorEnableCollision(false);
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


