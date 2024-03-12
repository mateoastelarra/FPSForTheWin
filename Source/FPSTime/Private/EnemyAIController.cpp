// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();

	if (AIBehavior != nullptr)
	{
		RunBehaviorTree(AIBehavior);

		APawn* Player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

		UBlackboardComponent* AIBlackboard = GetBlackboardComponent();
		if (GetPawn())
		{
			UE_LOG(LogTemp, Warning, TEXT("Start Location"));
			AIBlackboard->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());
		}
		
	}
}

void AEnemyAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}
