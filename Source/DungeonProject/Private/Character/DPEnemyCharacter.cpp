// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/DPEnemyCharacter.h"

#include "DPGameplayTags.h"
#include "AbilitySystem/DPAbilitySystemComponent.h"
#include "AbilitySystem/DPAbilitySystemLibrary.h"
#include "AbilitySystem/DPAttributeSet.h"
#include "AI/DPAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/WidgetComponent.h"
#include "DungeonProject/DungeonProject.h"
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
	
	HealthBar = CreateDefaultSubobject<UWidgetComponent>("HealthBar");
	HealthBar->SetupAttachment(GetRootComponent());

	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	GetMesh()->MarkRenderStateDirty();

	BaseWalkSpeed = 250.f;
}

void ADPEnemyCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (!HasAuthority()) return;

	DPAIController = Cast<ADPAIController> (NewController);
	DPAIController->GetBlackboardComponent()->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
	DPAIController->RunBehaviorTree(BehaviorTree);
	DPAIController->GetBlackboardComponent()->SetValueAsBool(FName("HitReacting"), false);
}

void ADPEnemyCharacter::HighlightActor_Implementation()
{
	GetMesh()->SetRenderCustomDepth(true);
}

void ADPEnemyCharacter::UnhighlightActor_Implementation()
{
	GetMesh()->SetRenderCustomDepth(false);
}

int32 ADPEnemyCharacter::GetPlayerLevel_Implementation()
{
	return Level;
}

void ADPEnemyCharacter::Die(const FVector& DeathImpulse)
{
	SetLifeSpan(LifeSpan);
	if (DPAIController) DPAIController->GetBlackboardComponent()->SetValueAsBool(FName("Dead"), true);
	//TODO : 보상 스폰
	Super::Die(DeathImpulse);
}

FVector ADPEnemyCharacter::GetCombatSocketLocation_Implementation(const FGameplayTag& MontageTag)
{
	const FDPGameplayTags& GameplayTags = FDPGameplayTags::Get();
	
	if (MontageTag.MatchesTagExact(GameplayTags.CombatSocket_LeftHand))
	{
		return GetMesh()->GetSocketLocation(LeftHandSocketName);
	}
	if (MontageTag.MatchesTagExact(GameplayTags.CombatSocket_RightHand))
	{
		return GetMesh()->GetSocketLocation(RightHandSocketName);
	}

	return FVector();
}

void ADPEnemyCharacter::HitReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount)
{
	bHitReacting = NewCount > 0;
	GetCharacterMovement()->MaxWalkSpeed = bHitReacting ? 0.f : BaseWalkSpeed;
	if (DPAIController && DPAIController->GetBlackboardComponent())
	{
		DPAIController->GetBlackboardComponent()->SetValueAsBool(FName("HitReacting"), bHitReacting);
	}
}

void ADPEnemyCharacter::SetCombatTarget_Implementation(AActor* InCombatTarget)
{
	CombatTarget = InCombatTarget;
}

AActor* ADPEnemyCharacter::GetCombatTarget_Implementation()
{
	return CombatTarget;
}

TSubclassOf<ADPProjectileBase> ADPEnemyCharacter::GetProjectileClass_Implementation()
{
	if (CharacterClass == ECharacterClass::Range || CharacterClass == ECharacterClass::Complex)
	{
		return ProjectileClass;	
	}
	return nullptr;
}

void ADPEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	GetCharacterMovement()->MaxWalkSpeed = BaseWalkSpeed;
	
}

void ADPEnemyCharacter::InitAbilityActorInfo()
{
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	Cast<UDPAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();
	AbilitySystemComponent->RegisterGameplayTagEvent(FDPGameplayTags::Get().Debuff_Stun, EGameplayTagEventType::NewOrRemoved).AddUObject(this, &ADPEnemyCharacter::StunTagChanged);


	if (HasAuthority())
	{
		InitializeDefaultAttributes();
	}
	OnASCRegistered.Broadcast(AbilitySystemComponent);
}

void ADPEnemyCharacter::InitializeDefaultAttributes() const
{
	UDPAbilitySystemLibrary::InitializeDefaultAttributes(this, CharacterClass, Level, AbilitySystemComponent);
}

void ADPEnemyCharacter::StunTagChanged(const FGameplayTag CallbackTag, int32 NewCount)
{
	Super::StunTagChanged(CallbackTag, NewCount);
	
	if (DPAIController && DPAIController->GetBlackboardComponent())
	{
		DPAIController->GetBlackboardComponent()->SetValueAsBool(FName("Stunned"), bIsStunned);
	}
}
