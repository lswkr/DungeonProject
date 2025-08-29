// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/DPCharacterBase.h"
#include "DPHeroCharacter.generated.h"

/**
 * 
 */

class ADPPlayerState;
class UCameraComponent;
class USpringArmComponent;

UCLASS()
class DUNGEONPROJECT_API ADPHeroCharacter : public ADPCharacterBase
{
	GENERATED_BODY()

public:
	ADPHeroCharacter();

	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

	UPROPERTY(EditDefaultsOnly)
	float DeathTime = 5.f;

	FTimerHandle DeathTimer;


private:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UCameraComponent> Camera;
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USpringArmComponent> SpringArm;

	virtual void InitAbilityActorInfo() override;
	
};
