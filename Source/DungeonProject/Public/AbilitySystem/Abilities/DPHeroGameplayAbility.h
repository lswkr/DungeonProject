// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/DPGameplayAbility.h"
#include "DPHeroGameplayAbility.generated.h"

class ADPHeroCharacter;
/**
 * 
 */
UCLASS()
class DUNGEONPROJECT_API UDPHeroGameplayAbility : public UDPGameplayAbility
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure)
	ADPHeroCharacter* GetHeroCharacterFromActorInfo();
	
private:
	TWeakObjectPtr<ADPHeroCharacter> CachedHeroCharacter;
};
