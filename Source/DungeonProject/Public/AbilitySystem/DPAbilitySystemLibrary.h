// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DPAbilityTypes.h"
#include "Kismet/BlueprintFunctionLibrary.h"
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

	/* Gameplay Mechanics */
	UFUNCTION(BlueprintCallable, Category = "DPAbilitySystemLibrary|GameplayMechanics")
	static bool bIsHostile(AActor* FirstActor, AActor* SecondActor);

	UFUNCTION(BlueprintCallable, Category = "DPAbilitySystemLibrary|GameplayMechanics")
	static FGameplayEffectContextHandle ApplyDamageEffect(const FDamageEffectParams& DamageEffectParams);

	
	
	/* Effect Context Setters */
	UFUNCTION(BlueprintCallable, Category = "DPAbilitySystemLibrary|GameplayEffect")
	static void SetDeathImpulse(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, const FVector& InImpulse);
};
