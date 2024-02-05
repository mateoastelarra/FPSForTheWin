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
	
	Gun = GetWorld()->SpawnActor<AGun>(GunClass);
	Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("SOCKET_Weapon_L"));
	Gun->SetOwner(this);
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
	Gun->PullTrigger();
}
