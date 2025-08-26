// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/DPAttributeSet.h"

#include "Net/UnrealNetwork.h"

void UDPAttributeSet::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	/* Primary Attributes */
	DOREPLIFETIME_CONDITION_NOTIFY(UDPAttributeSet, Strength, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDPAttributeSet, Intelligence, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDPAttributeSet, Luck, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDPAttributeSet, Will, COND_None, REPNOTIFY_Always);

	DOREPLIFETIME_CONDITION_NOTIFY(UDPAttributeSet, Attack, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDPAttributeSet, Defense, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDPAttributeSet, CriticalHitChance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDPAttributeSet, BlockChance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDPAttributeSet, HealthRegeneration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDPAttributeSet, ManaRegeneration, COND_None, REPNOTIFY_Always);
	
	DOREPLIFETIME_CONDITION_NOTIFY(UDPAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDPAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDPAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDPAttributeSet, Mana, COND_None, REPNOTIFY_Always);
}


void UDPAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
}

void UDPAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
}

void UDPAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
	Super::PostAttributeChange(Attribute, OldValue, NewValue);
}


void UDPAttributeSet::OnRep_Strength(const FGameplayAttributeData& OldStrength)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDPAttributeSet, Strength, OldStrength);
}

void UDPAttributeSet::OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDPAttributeSet, Intelligence, OldIntelligence);
}

void UDPAttributeSet::OnRep_Luck(const FGameplayAttributeData& OldLuck)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDPAttributeSet, Luck, OldLuck);
}

void UDPAttributeSet::OnRep_Will(const FGameplayAttributeData& OldWill)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDPAttributeSet, Will, OldWill);
}

void UDPAttributeSet::OnRep_Attack(const FGameplayAttributeData& OldAttack)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDPAttributeSet, Attack, OldAttack);
}

void UDPAttributeSet::OnRep_Defense(const FGameplayAttributeData& OldDefense)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDPAttributeSet, Defense, OldDefense);
}

void UDPAttributeSet::OnRep_CriticalHitChance(const FGameplayAttributeData& OldCriticalHitChance)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDPAttributeSet, CriticalHitChance, OldCriticalHitChance);
}

void UDPAttributeSet::OnRep_BlockChance(const FGameplayAttributeData& OldBlockChance)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDPAttributeSet, BlockChance, OldBlockChance);
}

void UDPAttributeSet::OnRep_HealthRegeneration(const FGameplayAttributeData& OldHealthRegeneration)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDPAttributeSet, HealthRegeneration, OldHealthRegeneration);
}

void UDPAttributeSet::OnRep_ManaRegeneration(const FGameplayAttributeData& OldManaRegeneration)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDPAttributeSet, ManaRegeneration, OldManaRegeneration);
}

void UDPAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDPAttributeSet, MaxHealth, OldMaxHealth);
}

void UDPAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDPAttributeSet, MaxMana, OldMaxMana);
}

void UDPAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDPAttributeSet, Health, OldHealth);
}

void UDPAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDPAttributeSet, Mana, OldMana);
}



