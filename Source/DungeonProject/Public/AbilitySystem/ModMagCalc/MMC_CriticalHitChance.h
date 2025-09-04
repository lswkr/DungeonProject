// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "MMC_CriticalHitChance.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONPROJECT_API UMMC_CriticalHitChance : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()

public:
	UMMC_CriticalHitChance();

	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;

private:
	FGameplayEffectAttributeCaptureDefinition AttDef;
	FGameplayEffectAttributeCaptureDefinition LuckDef;
};
