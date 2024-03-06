// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DoorActor.h"
#include "TwoSidesDoorActor.generated.h"

/**
 * 
 */
UCLASS()
class FPSTIME_API ATwoSidesDoorActor : public ADoorActor
{
	GENERATED_BODY()
	
public:
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;


};
