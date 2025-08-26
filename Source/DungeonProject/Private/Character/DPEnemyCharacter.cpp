// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/DPEnemyCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"

ADPEnemyCharacter::ADPEnemyCharacter()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bUseControllerDesiredRotation = true;
}

void ADPEnemyCharacter::HighlightActor_Implementation()
{
	GetMesh()->SetRenderCustomDepth(true);
}

void ADPEnemyCharacter::UnhighlightActor_Implementation()
{
	GetMesh()->SetRenderCustomDepth(false);
}

void ADPEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	GetCharacterMovement()->MaxWalkSpeed = BaseWalkSpeed;
	
}
