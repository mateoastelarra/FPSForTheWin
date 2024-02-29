// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyTower.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraShakeBase.h"
#include "Kismet/GameplayStatics.h"
#include "BaseProjectile.h"
#include "FPSTime/PlayerCharacter.h"
#include "TimerManager.h"
#include "Spawner.h"

// Sets default values
AEnemyTower::AEnemyTower()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComp;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(CapsuleComp);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(BaseMesh);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);
}

// Called when the game starts or when spawned
void AEnemyTower::BeginPlay()
{
	Super::BeginPlay();
	
	Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
	GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &AEnemyTower::CheckFireCondition, FireRate, true);
}

// Called every frame
void AEnemyTower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (InFireRange())
	{
		RotateTurret(Player->GetActorLocation());
	}
}

// Called to bind functionality to input
void AEnemyTower::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemyTower::RotateTurret(FVector LookAtTarget)
{
	FVector ToTarget = LookAtTarget - TurretMesh->GetComponentLocation();
	FRotator LookAtRotation = FRotator(0.f, ToTarget.Rotation().Yaw, 0.f);
	TurretMesh->SetWorldRotation(
		FMath::RInterpTo(
			TurretMesh->GetComponentRotation(),
			LookAtRotation,
			UGameplayStatics::GetWorldDeltaSeconds(this),
			RotationSpeed));
}

void AEnemyTower::Fire()
{
	FVector Location = ProjectileSpawnPoint->GetComponentLocation();
	FRotator Rotation = ProjectileSpawnPoint->GetComponentRotation();

	ABaseProjectile* Projectile = GetWorld()->SpawnActor<ABaseProjectile>(ProjectileClass, Location, Rotation);
	Projectile->SetOwner(this);
}

void AEnemyTower::CheckFireCondition()
{
	if (Player && InFireRange())
	{
		Fire();
	}
}

bool AEnemyTower::InFireRange()
{
	if (Player)
	{
		float DistanceToPlayer = FVector::Distance(GetActorLocation(), Player->GetActorLocation());
		if (DistanceToPlayer < FireRange)
		{
			return true;
		}
	}
	return false;
}

void AEnemyTower::Destroyed()
{
	if (WasDestroyed) { return; }
	WasDestroyed = true;

	if (DeathParticles)
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, DeathParticles, GetActorLocation(), GetActorRotation());
	}
	if (DeathSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetActorLocation());
	}
	if (DeathCameraShakeClass)
	{
		GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(DeathCameraShakeClass);
	}
	EnemySpawner->RemoveFromSpawnedActors(this);	
	Destroy();
}
