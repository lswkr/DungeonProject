// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/DPPlayerState.h"

#include "AbilitySystem/DPAbilitySystemComponent.h"
#include "AbilitySystem/DPAttributeSet.h"
#include "Net/UnrealNetwork.h"

ADPPlayerState::ADPPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UDPAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<UDPAttributeSet> (TEXT("AttributeSet"));

	NetUpdateFrequency = 100.f;
}

void ADPPlayerState::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ADPPlayerState, Level);
	DOREPLIFETIME(ADPPlayerState, XP);
	DOREPLIFETIME(ADPPlayerState, AttributePoints);
	DOREPLIFETIME(ADPPlayerState, SpellPoints);
}

void ADPPlayerState::OnRep_Level(int32 OldLevel)
{
	
}

void ADPPlayerState::OnRep_XP(int32 OldXP)
{
	
}

void ADPPlayerState::OnRep_AttributePoints(int32 OldAttributePoints)
{
	
}

void ADPPlayerState::OnRep_SpellPoints(int32 OldSpellPoints)
{
	
}

UAbilitySystemComponent* ADPPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
