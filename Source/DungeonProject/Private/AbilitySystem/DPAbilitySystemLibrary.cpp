// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/DPAbilitySystemLibrary.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "DPGameplayTags.h"
#include "Game/DPGameModeBase.h"
#include "Kismet/GameplayStatics.h"

UAbilityInfo* UDPAbilitySystemLibrary::GetAbilityInfo(const UObject* WorldContextObject)
{
	const ADPGameModeBase* DPGameMode = Cast<ADPGameModeBase> (UGameplayStatics::GetGameMode(WorldContextObject));
	if (DPGameMode == nullptr) return nullptr;
	return DPGameMode->AbilityInfo;
}

bool UDPAbilitySystemLibrary::bIsHostile(AActor* FirstActor, AActor* SecondActor)
{
	const bool bBothArePlayers = FirstActor->ActorHasTag(FName("Player")) && SecondActor->ActorHasTag(FName("Player"));
	const bool bBothAreEnemies = FirstActor->ActorHasTag(FName("Enemy")) && SecondActor->ActorHasTag(FName("Enemy"));

	return !(bBothArePlayers || bBothAreEnemies);
}

FGameplayEffectContextHandle UDPAbilitySystemLibrary::ApplyDamageEffect(const FDamageEffectParams& DamageEffectParams)
{
	const FDPGameplayTags& DPGameplayTags = FDPGameplayTags::Get();
	const AActor* SourceAvatarActor = DamageEffectParams.SourceAbilitySystemComponent->GetAvatarActor();

	FGameplayEffectContextHandle EffectContextHandle =  DamageEffectParams.SourceAbilitySystemComponent->MakeEffectContext();
	EffectContextHandle.AddSourceObject(SourceAvatarActor);
	SetDeathImpulse(EffectContextHandle, DamageEffectParams.DeathImpulse);

	const FGameplayEffectSpecHandle SpecHandle = DamageEffectParams.SourceAbilitySystemComponent->MakeOutgoingSpec(DamageEffectParams.DamageGameplayEffectClass, DamageEffectParams.AbilityLevel,EffectContextHandle);

	DamageEffectParams.TargetAbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data);
	return EffectContextHandle;
}

void UDPAbilitySystemLibrary::SetDeathImpulse(FGameplayEffectContextHandle& EffectContextHandle,
	const FVector& InImpulse)
{
	if (FDPGameplayEffectContext* DPEffectContext = static_cast<FDPGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		DPEffectContext->SetDeathImpulse(InImpulse);
	}
}
