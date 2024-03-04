// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DoorActor.generated.h"

UCLASS()
class FPSTIME_API ADoorActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ADoorActor();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	void NotifyActorBeginOverlap(AActor* OtherActor) override;

private:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* Trigger;

	UPROPERTY(EditAnywhere)
	int KeysNeededToOpen;

	UPROPERTY(EditAnywhere)
	FVector MoveOffset;

	UPROPERTY(EditAnywhere)
	float MoveTime = 4;

	UPROPERTY(EditAnywhere)
	float MovementPrecission = 0.1;

	bool bShouldMove = false;

	FVector OriginalLocation;

	void Open(float DeltaTime);

};
