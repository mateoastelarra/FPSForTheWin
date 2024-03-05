// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorActor.h"
#include "Components/PrimitiveComponent.h"
#include "Components/BoxComponent.h"
#include "FPSTime/PlayerCharacter.h"
#include "KillForKeysGameMode.h"

// Sets default values
ADoorActor::ADoorActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	Trigger->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void ADoorActor::BeginPlay()
{
	Super::BeginPlay();
	
	OriginalLocation = GetActorLocation();
}

// Called every frame
void ADoorActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bShouldMove)
	{
		Open(DeltaTime);
	}
}

void ADoorActor::NotifyActorBeginOverlap(AActor* OtherActor)
{
	APlayerCharacter* Player = Cast<APlayerCharacter>(OtherActor);
	if (Player)
	{
		AGameModeBase* AuthGameMode = GetWorld()->GetAuthGameMode();
		AKillForKeysGameMode* CurrentGameMode = Cast<AKillForKeysGameMode>(GetWorld()->GetAuthGameMode());
		if (CurrentGameMode)
		{
			int CurrentKeys = CurrentGameMode->GetCurrentKeys();
			FString PlayerMessage;
			if (CurrentKeys >= KeysNeededToOpen)
			{
				bShouldMove = true;
				CurrentGameMode->LoseKeys(KeysNeededToOpen);
				PlayerMessage = TEXT("You used The keys.");	
			}
			else
			{
				PlayerMessage = TEXT("You need 2 keys to open this door.");
			}
			CurrentGameMode->SetPlayerMessage(PlayerMessage);
			CurrentGameMode->SetPlayerMessageUIVisibility(true);
		}
	}
}

void ADoorActor::NotifyActorEndOverlap(AActor* OtherActor)
{
	APlayerCharacter* Player = Cast<APlayerCharacter>(OtherActor);
	if (Player)
	{
		AGameModeBase* AuthGameMode = GetWorld()->GetAuthGameMode();
		AKillForKeysGameMode* CurrentGameMode = Cast<AKillForKeysGameMode>(GetWorld()->GetAuthGameMode());
		if (CurrentGameMode)
		{
			CurrentGameMode->SetPlayerMessageUIVisibility(false);
		}
	}
}

void ADoorActor::Open(float DeltaTime)
{
	FVector TargetLocation = OriginalLocation + MoveOffset;
	FVector CurrentLocation = GetActorLocation();
	float Speed = MoveOffset.Length() / MoveTime;
	FVector NewPosition = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaTime, Speed);
	SetActorLocation(NewPosition);
	if (FVector::Distance(TargetLocation, CurrentLocation) <= MovementPrecission)
	{
		bShouldMove = false;
	}
}

