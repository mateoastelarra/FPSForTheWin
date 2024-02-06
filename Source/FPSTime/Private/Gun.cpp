// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "Components/SkeletalMeshComponent.h"

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
	CurrentBullets--;

	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn == nullptr) { return; }

	AController* OwnerController = OwnerPawn->GetController();
	if (OwnerController == nullptr) { return; }

	FVector Start;
	FRotator Rotation;
	OwnerController->GetPlayerViewPoint(Start, Rotation);

	FVector End = Start + Rotation.Vector() * MaxRange;

	FHitResult OutHit;

	bool bHit = GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECollisionChannel::ECC_GameTraceChannel1);
	DrawDebugLine(GetWorld(), Start, End, FColor::Red, true);
	if (bHit)
	{
		FVector ShotDirection = -Rotation.Vector();
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, OutHit.Location, ShotDirection.Rotation());

		AActor* HitActor = OutHit.GetActor();
		DrawDebugPoint(GetWorld(), OutHit.Location, 20, FColor::Red, true);

		if (HitActor)
		{
		}
	}
}

void AGun::AddBullets(int BulletsToAdd)
{
	CurrentBullets += BulletsToAdd;
}

