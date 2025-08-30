// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DPAbilityTypes.h"
#include "DPProjectileBase.generated.h"

class UBoxComponent;
class UProjectileMovementComponent;
class UNiagaraSystem;
class UNiagaraComponent;

UENUM(BlueprintType)
enum class EProjectileType : uint8
{
	EOnHit,
	EOnOverlap
};

UCLASS()
class DUNGEONPROJECT_API ADPProjectileBase : public AActor
{
	GENERATED_BODY()
	
public:	
	ADPProjectileBase();

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UProjectileMovementComponent> ProjectileMovement;

	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn = true))
	FDamageEffectParams DamageEffectParams;

	UPROPERTY(EditDefaultsOnly)
	EProjectileType ProjectileType = EProjectileType::EOnHit;

	UPROPERTY(EditDefaultsOnly)
	bool bIsGuided = false;

	UPROPERTY()
	TObjectPtr<USceneComponent> HomingTargetSceneComponent;
	
protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	virtual void OnHit();

	virtual void Destroyed() override;

	UFUNCTION()
	virtual void OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UBoxComponent* BoxComponent;

	bool IsValidOverlap(AActor* OverlappedActor);
	bool bHit = false;

	UPROPERTY()
	TObjectPtr<UAudioComponent> LoopingSoundComponent;

private:
	UPROPERTY(EditDefaultsOnly)
	float LifeSpan = 5.f;
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UNiagaraSystem> ImpactEffect;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USoundBase> ImpactSound;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USoundBase> LoopingSound;



};
