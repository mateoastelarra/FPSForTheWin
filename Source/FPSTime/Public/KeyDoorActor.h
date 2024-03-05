// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DoorActor.h"
#include "KeyDoorActor.generated.h"

/**
 * 
 */
UCLASS()
class FPSTIME_API AKeyDoorActor : public ADoorActor
{
	GENERATED_BODY()
	
public:
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

private:
	UPROPERTY(EditAnywhere)
	int KeysNeededToOpen;
};
