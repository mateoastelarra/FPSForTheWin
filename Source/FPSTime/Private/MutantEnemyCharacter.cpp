// Fill out your copyright notice in the Description page of Project Settings.


#include "MutantEnemyCharacter.h"
#include "Components/BoxComponent.h"
#include "FPSTime/PlayerCharacter.h"
#include "Health.h"
#include "Animation/AnimInstance.h"

AMutantEnemyCharacter::AMutantEnemyCharacter()
{
	AttackTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	AttackTrigger->SetupAttachment(RootComponent);
}

void AMutantEnemyCharacter::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Player = Cast<APlayerCharacter>(OtherActor);
	if (Player)
	{
		bPlayerInAttackRange = true;
	}
}

void AMutantEnemyCharacter::NotifyActorEndOverlap(AActor* OtherActor)
{
	Player = Cast<APlayerCharacter>(OtherActor);
	if (Player)
	{
		bPlayerInAttackRange = false;
		Player = nullptr;
	}
}

void AMutantEnemyCharacter::Attack()
{
	if (bPlayerInAttackRange && Player)
	{
		Super::Attack();

		UAnimInstance* MutantAnimInstance = GetMesh()->GetAnimInstance();
		if (MutantAnimInstance && AttackAnimMontage)
		{
			MutantAnimInstance->Montage_Play(AttackAnimMontage);
		}
		
		UHealth* PlayerHealthComponent = Player->FindComponentByClass<UHealth>();
		if (PlayerHealthComponent)
		{
			PlayerHealthComponent->TakeDamage(Damage);
		}
	}	
}

void AMutantEnemyCharacter::Intimidate()
{
	UE_LOG(LogTemp, Warning, TEXT("I´m a big and scary motherfucker"));
}
