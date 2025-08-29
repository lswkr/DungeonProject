// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/DPEnemyCharacter.h"

#include "AbilitySystem/DPAbilitySystemComponent.h"
#include "AbilitySystem/DPAttributeSet.h"
#include "GameFramework/CharacterMovementComponent.h"

ADPEnemyCharacter::ADPEnemyCharacter()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

	AbilitySystemComponent = CreateDefaultSubobject<UDPAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
	
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bUseControllerDesiredRotation = true;

	AttributeSet = CreateDefaultSubobject<UDPAttributeSet> (TEXT("AttributeSet"));

	BaseWalkSpeed = 250.f;
}

void ADPEnemyCharacter::HighlightActor_Implementation()
{
	GetMesh()->SetRenderCustomDepth(true);
}

void ADPEnemyCharacter::UnhighlightActor_Implementation()
{
	GetMesh()->SetRenderCustomDepth(false);
}

void ADPEnemyCharacter::SetCombatTarget_Implementation(AActor* InCombatTarget)
{
	CombatTarget = InCombatTarget;
}

AActor* ADPEnemyCharacter::GetCombatTarget_Implementation()
{
	return CombatTarget;
}

void ADPEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	GetCharacterMovement()->MaxWalkSpeed = BaseWalkSpeed;
	
}
