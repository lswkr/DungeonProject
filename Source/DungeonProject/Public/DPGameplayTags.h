// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

/**
 * 
 */

struct FDPGameplayTags
{
public:
	static const FDPGameplayTags& Get() { return GameplayTags; }
	static void InitializeNativeGameplayTags();


	FGameplayTag Abilities_Status_Equipped;
	
	/* Primary Attributes */
	FGameplayTag Attributes_Primary_Strength;
	FGameplayTag Attributes_Primary_Intelligence;
	FGameplayTag Attributes_Primary_Luck;
	FGameplayTag Attributes_Primary_Will;
	
	/* Secondary Attributes */
	FGameplayTag Attributes_Secondary_Attack;
	FGameplayTag Attributes_Secondary_Defense;
	FGameplayTag Attributes_Secondary_CriticalHitChance;
	FGameplayTag Attributes_Secondary_BlockChance;
	FGameplayTag Attributes_Secondary_HealthRegeneration;
	FGameplayTag Attributes_Secondary_ManaRegeneration;
	
	/* Vital Attributes */
	FGameplayTag Attributes_Vital_MaxHealth;
	FGameplayTag Attributes_Vital_MaxMana;
	FGameplayTag Attributes_Vital_Health;
	FGameplayTag Attributes_Vital_Mana;
	
	
private:
	static FDPGameplayTags GameplayTags;
};
