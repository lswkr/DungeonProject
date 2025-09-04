// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DPAbilityTypes.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Data/CharacterClassInfo.h"
#include "DPAbilitySystemLibrary.generated.h"

/**
 * 
 */

class UAbilityInfo;

UCLASS()
class DUNGEONPROJECT_API UDPAbilitySystemLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/* Ability System Class Default */
	UFUNCTION(BlueprintCallable, Category = "DPAbilitySystemLibrary|CharacterClassDefault")
	static UAbilityInfo* GetAbilityInfo(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category="DPAbilitySystemLibrary|CharacterClassDefaults")
	static void InitializeDefaultAttributes(const UObject* WorldContextObject, ECharacterClass CharacterClass, float Level, UAbilitySystemComponent* ASC);

	UFUNCTION(BlueprintCallable, Category="DPAbilitySystemLibrary|CharacterClassDefaults")
	static UCharacterClassInfo* GetCharacterClassInfo(const UObject* WorldContextObject);
	
	/* Gameplay Mechanics */
	UFUNCTION(BlueprintCallable, Category = "DPAbilitySystemLibrary|GameplayMechanics")
	static bool bIsHostile(AActor* FirstActor, AActor* SecondActor);

	UFUNCTION(BlueprintCallable, Category = "DPAbilitySystemLibrary|GameplayMechanics")
	static FGameplayEffectContextHandle ApplyDamageEffect(const FDamageEffectParams& DamageEffectParams);

	static int32 GetXPRewardForClassAndLevel(const UObject* WorldContextObject, int32 CharacterLevel);

	
	/* Effect Context Setters */
	UFUNCTION(BlueprintCallable, Category = "DPAbilitySystemLibrary|GameplayEffect")
	static void SetDeathImpulse(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, const FVector& InImpulse);
};
