// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Collectable.generated.h"

UCLASS()
class FPSTIME_API ACollectable : public AActor
{
	GENERATED_BODY()
	
public:	
	ACollectable();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void Use(AActor* User);

private:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
	FString NameToShowOnScreen;

	UPROPERTY(EditAnywhere)
	USoundBase* CollectSound;

	UPROPERTY(EditAnywhere)
	FRotator RotationAmount;

	UPROPERTY(EditAnywhere)
	float RotationDelay;

	FTimerHandle Timer;

	void RotationTimer();
};
