// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/DPAbilitySystemComponent.h"

#include "DPGameplayTags.h"
#include "AbilitySystem/Abilities/DPGameplayAbility.h"

void UDPAbilitySystemComponent::AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& StartupAbilities)
{
	for (const TSubclassOf<UGameplayAbility> AbilityClass : StartupAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, 1);
		if (const UDPGameplayAbility* DPAbility = Cast<UDPGameplayAbility>(AbilitySpec.Ability))
		{
			AbilitySpec.DynamicAbilityTags.AddTag(DPAbility->StartupInputTag);
			AbilitySpec.DynamicAbilityTags.AddTag(FDPGameplayTags::Get().Abilities_Status_Equipped);
			GiveAbility(AbilitySpec);
		}
	}
}
