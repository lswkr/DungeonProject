// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/DPCharacterBase.h"
#include "Interaction/EnemyInterface.h"
#include "Interaction/HighlightInterface.h"
#include "DPEnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONPROJECT_API ADPEnemyCharacter : public ADPCharacterBase, public IHighlightInterface, public IEnemyInterface
{
	GENERATED_BODY()

public:
	ADPEnemyCharacter();
	/* Highlight Interface */
	virtual void HighlightActor_Implementation() override;
	virtual void UnhighlightActor_Implementation() override;
	/* End Highlight Interface */

	/* Enemy Interface */
	void SetCombatTarget_Implementation(AActor* InCombatTarget);
	AActor* GetCombatTarget_Implementation();
	/* End Enemy Interface */
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite, Category = "Combat")
	TObjectPtr<AActor> CombatTarget;
};
