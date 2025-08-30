// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/DPHeroGameplayAbility.h"

#include "Character/DPHeroCharacter.h"

ADPHeroCharacter* UDPHeroGameplayAbility::GetHeroCharacterFromActorInfo()
{
	if (!CachedHeroCharacter.IsValid())
	{
		CachedHeroCharacter = Cast<ADPHeroCharacter>(GetOwningActorFromActorInfo());
	}
	return CachedHeroCharacter.IsValid()? CachedHeroCharacter.Get() : nullptr;
}
