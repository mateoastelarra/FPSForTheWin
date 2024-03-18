// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_Intimidate.generated.h"

/**
 * 
 */
UCLASS()
class FPSTIME_API UBTTask_Intimidate : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTask_Intimidate();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
