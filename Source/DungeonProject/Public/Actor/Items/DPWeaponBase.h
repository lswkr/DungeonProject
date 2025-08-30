// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DPAbilityTypes.h"
#include "Actor/Items/DPItemBase.h"
#include "DPWeaponBase.generated.h"

/**
 * 
 */

class UBoxComponent;

UCLASS()
class DUNGEONPROJECT_API ADPWeaponBase : public ADPItemBase
{
	GENERATED_BODY()
public:
	ADPWeaponBase();

	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn = true))
	FDamageEffectParams DamageEffectParams;

	UFUNCTION(BlueprintPure)
	UBoxComponent* GetCollisionBoxComponent() const {return BoxComponent;}
	
protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* BoxComponent;

	UPROPERTY(EditDefaultsOnly)
	USkeletalMeshComponent* SkeletalMeshComponent;
	
	UFUNCTION()
	virtual void OnHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	
};
