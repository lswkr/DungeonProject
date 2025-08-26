// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/DPCharacterBase.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/DPAbilitySystemComponent.h"
#include "Components/CapsuleComponent.h"


ADPCharacterBase::ADPCharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetCapsuleComponent()->SetGenerateOverlapEvents(false);
	GetMesh()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetMesh()->SetGenerateOverlapEvents(true);
}


void ADPCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
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
}

void ADPCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADPCharacterBase::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

UAbilitySystemComponent* ADPCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}


