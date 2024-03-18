// Fill out your copyright notice in the Description page of Project Settings.


#include "MutantEnemyCharacter.h"

void AMutantEnemyCharacter::Attack()
{
	Super::Attack();
	UE_LOG(LogTemp, Warning, TEXT("ARRGHH"));
}
