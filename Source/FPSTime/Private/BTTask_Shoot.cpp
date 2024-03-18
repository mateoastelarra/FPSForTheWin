// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Shoot.h"
#include "AIController.h"
#include "BaseEnemyCharacter.h"

UBTTask_Shoot::UBTTask_Shoot()
{
	NodeName = TEXT("Shoot");
}

EBTNodeResult::Type UBTTask_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AAIController* AIController = OwnerComp.GetAIOwner();
	if (AIController == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	
	ABaseEnemyCharacter* Enemy = Cast<ABaseEnemyCharacter>(AIController->GetPawn());
	if (Enemy == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	Enemy->Attack();
	return EBTNodeResult::Succeeded;
}
