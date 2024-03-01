// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "Health.h"
#include "Components/SkeletalMeshComponent.h"
#include "FPSTime/PlayerCharacter.h"

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
	
	CurrentBullets = MaxBullets;
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGun::PullTrigger()
{
	if (CurrentBullets <= 0) { return; }

	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("SOCKET_MuzzleFlash"));
	UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
	CurrentBullets--;

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
			UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation());
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
	CurrentBullets += BulletsToAdd;
}