// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/DPCharacterBase.h"
#include "Interaction/HighlightInterface.h"
#include "DPEnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONPROJECT_API ADPEnemyCharacter : public ADPCharacterBase, public IHighlightInterface
{
	GENERATED_BODY()

public:
	ADPEnemyCharacter();
	/* Highlight Interface */
	virtual void HighlightActor_Implementation() override;
	virtual void UnhighlightActor_Implementation() override;
	/* End Highlight Interface */

protected:
	virtual void BeginPlay() override;
};
