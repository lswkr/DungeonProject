// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/DPCharacterBase.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/DPAbilitySystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "MotionWarpingComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"


ADPCharacterBase::ADPCharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetCapsuleComponent()->SetGenerateOverlapEvents(false);
	GetMesh()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetMesh()->SetGenerateOverlapEvents(true);
	MotionWarpingComponent = CreateDefaultSubobject<UMotionWarpingComponent>(TEXT("MotionWarpingComponent"));
	
}


void ADPCharacterBase::MulticastHandleDeath_Implementation(const FVector& DeathImpulse)
{
	UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetActorLocation(), GetActorRotation());

	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->SetEnableGravity(true);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	GetMesh()->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	GetMesh()->AddImpulse(DeathImpulse, NAME_None, true);

	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	bDead = true;
	//StunDebuffComponent->Deactivate();
}

void ADPCharacterBase::OnRep_Stunned()
{
	
}

void ADPCharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

void ADPCharacterBase::StunTagChanged(const FGameplayTag CallbackTag, int32 NewCount)
{
	bIsStunned = NewCount > 0;
	GetCharacterMovement()->MaxWalkSpeed = bIsStunned ? 0.f : BaseWalkSpeed;
}

void ADPCharacterBase::InitAbilityActorInfo()
{
}

void ADPCharacterBase::ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level) const
{
	check(IsValid(GetAbilitySystemComponent()));
	check(GameplayEffectClass);

	FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	ContextHandle.AddSourceObject(this);
	const FGameplayEffectSpecHandle SpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(GameplayEffectClass, Level, ContextHandle);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), GetAbilitySystemComponent());
}

void ADPCharacterBase::InitializeDefaultAttributes() const
{
	ApplyEffectToSelf(DefaultPrimaryAttributes, 1.f);
	ApplyEffectToSelf(DefaultSecondaryAttributes, 1.f);
	ApplyEffectToSelf(DefaultVitalAttributes, 1.f);
}

void ADPCharacterBase::AddCharacterAbilities()
{
	UDPAbilitySystemComponent* DPASC = Cast<UDPAbilitySystemComponent>(AbilitySystemComponent);
	if (!HasAuthority()) return;

	DPASC->AddCharacterAbilities(StartupAbilities);
	DPASC->AddCharacterPassiveAbilities(StartupPassiveAbilities);
}


void ADPCharacterBase::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ADPCharacterBase, bIsStunned);
}

float ADPCharacterBase::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	const float DamageTaken = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	OnDamageDelegate.Broadcast(DamageTaken);
	return DamageTaken;
}

UAbilitySystemComponent* ADPCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UAnimMontage* ADPCharacterBase::GetHitReactMontage_Implementation()
{
	return HitReactMontage;
}

FVector ADPCharacterBase::GetCombatSocketLocation_Implementation(const FGameplayTag& MontageTag)
{
	return ICombatInterface::GetCombatSocketLocation_Implementation(MontageTag);
}

bool ADPCharacterBase::IsDead_Implementation() const
{
	return bDead;
}

AActor* ADPCharacterBase::GetAvatarActor_Implementation()
{
	return this;
}

TArray<FTaggedMontage> ADPCharacterBase::GetAttackMontages_Implementation()
{
	return AttackMontages;
}

UNiagaraSystem* ADPCharacterBase::GetHitEffect_Implementation()
{
	return HitEffect;
}

FTaggedMontage ADPCharacterBase::GetTaggedMontageByTag_Implementation(const FGameplayTag& MontageTag)
{
	for (FTaggedMontage TaggedMontage : AttackMontages)
	{
		if (TaggedMontage.MontageTag == MontageTag)
		{
			return TaggedMontage;
		}
	}
	return FTaggedMontage();
}

ECharacterClass ADPCharacterBase::GetCharacterClass_Implementation()
{
	return CharacterClass;
}

FOnASCRegistered& ADPCharacterBase::GetOnASCRegisteredDelegate()
{
	return OnASCRegistered;
}

void ADPCharacterBase::Die(const FVector& DeathImpulse)
{
	MulticastHandleDeath(DeathImpulse);
}

FOnDeathSignature& ADPCharacterBase::GetOnDeathDelegate()
{
	return OnDeathDelegate;
}

FOnDamageSignature& ADPCharacterBase::GetOnDamageDelegate()
{
	return OnDamageDelegate;
}


