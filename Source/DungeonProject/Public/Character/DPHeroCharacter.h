// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/DPCharacterBase.h"
#include "Interaction/PlayerInterface.h"

#include "DPHeroCharacter.generated.h"

/**
 * 
 */

class ADPPlayerState;
class UCameraComponent;
class USpringArmComponent;
class ADPWeaponBase;
UCLASS()
class DUNGEONPROJECT_API ADPHeroCharacter : public ADPCharacterBase, public IPlayerInterface
{
	GENERATED_BODY()

public:
	ADPHeroCharacter();

	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

	UPROPERTY(EditDefaultsOnly)
	float DeathTime = 5.f;

	FTimerHandle DeathTimer;

	UFUNCTION(BlueprintCallable)
	ADPWeaponBase* GetWeapon() const {return Weapon;}

	virtual void ToggleCollision_Implementation(bool bShouldEnable) override;
	
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UCameraComponent> Camera;
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USpringArmComponent> SpringArm;
	
	UPROPERTY()
	TObjectPtr<ADPWeaponBase> Weapon;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TSubclassOf<ADPWeaponBase> WeaponClass;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName WeaponSocketName;
	
	virtual void InitAbilityActorInfo() override;
	
};
