// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterEnemyCharacter.h"
#include "Gun.h"

void AShooterEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	Gun = GetWorld()->SpawnActor<AGun>(GunClass);
	GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);
	Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
	Gun->SetOwner(this);
}

void AShooterEnemyCharacter::Attack()
{
	Super::Attack();
	Gun->PullTrigger();
}
