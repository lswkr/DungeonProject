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

	/* Primary Attributes */
	FGameplayTag Attributes_Primary_Strength;
	FGameplayTag Attributes_Primary_Intelligence;
	FGameplayTag Attributes_Primary_Luck;
	FGameplayTag Attributes_Primary_Will;
	
	/* Secondary Attributes */

	/* Vital Attributes */
	
private:
	static FDPGameplayTags GameplayTags;
};
