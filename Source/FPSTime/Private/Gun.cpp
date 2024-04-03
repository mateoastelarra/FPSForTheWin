// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "Health.h"
#include "Components/SkeletalMeshComponent.h"
#include "FPSTime/PlayerCharacter.h"
#include "Engine/Texture2D.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	
	CurrentLoadedBullets = FMath::Min(StartingBullets, BulletsCapacity);
	RemainingBullets = FMath::Max(0, StartingBullets - BulletsCapacity);
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGun::PullTrigger()
{
	if (CurrentLoadedBullets <= 0) 
	{ 
		UGameplayStatics::SpawnSoundAttached(EmptySound, Mesh, TEXT("SOCKET_MuzzleFlash"));
		return; 
	}

	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("SOCKET_MuzzleFlash"));
	UGameplayStatics::SpawnSoundAttached(FireSound, Mesh, TEXT("SOCKET_MuzzleFlash"));
	CurrentLoadedBullets--;

	FVector ShotDirection;
	FHitResult OutHit;
	bool bHit = GunTrace(OutHit, ShotDirection);

	//DrawDebugLine(GetWorld(), Start, End, FColor::Red, true);
	if (bHit)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, OutHit.Location, ShotDirection.Rotation());

		AActor* HitActor = OutHit.GetActor();
		//DrawDebugPoint(GetWorld(), OutHit.Location, 20, FColor::Red, true);

		if (HitActor)
		{
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), HitSound, OutHit.Location);
			UHealth* HitHealthComponent = HitActor->FindComponentByClass<UHealth>();
			if (HitHealthComponent)
			{
				HitHealthComponent->TakeDamage(Damage);
			}
		}
	}
}

bool AGun::GunTrace(FHitResult& Hit, FVector& ShotDirection)
{
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn == nullptr) { return false; }

	AController* OwnerController = OwnerPawn->GetController();
	if (OwnerController == nullptr) { return false; }

	FVector Start;
	FRotator Rotation;
	OwnerController->GetPlayerViewPoint(Start, Rotation);
	ShotDirection = -Rotation.Vector();
	FVector End = Start + Rotation.Vector() * MaxRange;

	bool bHit;
	if (Cast<APlayerCharacter>(OwnerPawn))
	{
		bHit = GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECollisionChannel::ECC_GameTraceChannel1);
	}
	else
	{
		bHit = GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECollisionChannel::ECC_GameTraceChannel2);
	}
	return bHit;
}

void AGun::AddBullets(int BulletsToAdd)
{
	RemainingBullets += BulletsToAdd;
}

int AGun::GetCurrentBullets()
{
	return CurrentLoadedBullets;
}

float AGun::GetShootingRate()
{
	return ShootingRate;
}

int AGun::GetCurrentGunAmmo()
{
	return CurrentLoadedBullets;
}

int AGun::GetRemainingAmmo()
{
	return RemainingBullets;
}

void AGun::Reload()
{
	UGameplayStatics::SpawnSoundAttached(ReloadSound, Mesh, TEXT("SOCKET_MuzzleFlash"));
	int BulletsToAdd = FMath::Min(BulletsCapacity - CurrentLoadedBullets, RemainingBullets);
	CurrentLoadedBullets += BulletsToAdd;
	RemainingBullets -= BulletsToAdd;
}

UStaticMeshComponent* AGun::GetClipMesh()
{
	return Clip;
}

UTexture2D* AGun::GetImageWeaponBody()
{
	return ImageWeaponBody;
}

UTexture2D* AGun::GetImageWeaponMagazine()
{
	return ImageWeaponMagazine;
}
