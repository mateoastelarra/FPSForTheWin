// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_PlayerLocationIfSeen.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "AIController.h"
#include "BaseEnemyCharacter.h"

UBTService_PlayerLocationIfSeen::UBTService_PlayerLocationIfSeen()
{
	NodeName = TEXT("Update Player Location If Seen");
}

void UBTService_PlayerLocationIfSeen::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	APawn* Player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (Player == nullptr) { return; }

	AAIController* AIController = OwnerComp.GetAIOwner();
	if (AIController == nullptr){ return; }

	ABaseEnemyCharacter* Enemy = Cast<ABaseEnemyCharacter>(AIController->GetPawn());
	if (Enemy == nullptr) { return; }
	//AIController->LineOfSightTo(Player)
	if (FVector::Distance(Player->GetActorLocation(), Enemy->GetActorLocation()) < 1000)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), Player->GetActorLocation());
	}
	else
	{
		OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
	}
}
