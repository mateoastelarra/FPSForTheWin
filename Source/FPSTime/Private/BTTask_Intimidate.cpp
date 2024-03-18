// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Intimidate.h"
#include "AIController.h"
#include "MutantEnemyCharacter.h"

UBTTask_Intimidate::UBTTask_Intimidate()
{
	NodeName = TEXT("Intimidate");
}

EBTNodeResult::Type UBTTask_Intimidate::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AAIController* AIController = OwnerComp.GetAIOwner();
	if (AIController == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	AMutantEnemyCharacter* Enemy = Cast<AMutantEnemyCharacter>(AIController->GetPawn());
	if (Enemy == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	Enemy->Intimidate();
	return EBTNodeResult::Succeeded;
}
