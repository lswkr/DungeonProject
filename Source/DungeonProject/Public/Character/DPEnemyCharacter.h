// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/DPCharacterBase.h"
#include "Interaction/EnemyInterface.h"
#include "Interaction/HighlightInterface.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "DPEnemyCharacter.generated.h"

/**
 * 
 */

class UBehaviorTree;
class ADPAIController;
class UWidgetComponent;

UCLASS()
class DUNGEONPROJECT_API ADPEnemyCharacter : public ADPCharacterBase, public IHighlightInterface, public IEnemyInterface
{
	GENERATED_BODY()

public:
	ADPEnemyCharacter();
	virtual void PossessedBy(AController* NewController) override;
	
	/* Highlight Interface */
	virtual void HighlightActor_Implementation() override;
	virtual void UnhighlightActor_Implementation() override;
	/* End Highlight Interface */

	/* Combat Interface*/
	virtual int32 GetPlayerLevel_Implementation() override;
	virtual void Die(const FVector& DeathImpulse) override;
	virtual FVector GetCombatSocketLocation_Implementation(const FGameplayTag& MontageTag) override;
	/* End Combat Interface*/
	
	/* Enemy Interface */
	void SetCombatTarget_Implementation(AActor* InCombatTarget);
	AActor* GetCombatTarget_Implementation();
	TSubclassOf<ADPProjectileBase> GetProjectileClass_Implementation();
	/* End Enemy Interface */

	UPROPERTY(BlueprintReadWrite, Category = "Combat")
	TObjectPtr<AActor> CombatTarget;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnMaxHealthChanged;

	void HitReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount);

	UPROPERTY(BlueprintReadOnly, Category = "Combat")
	bool bHitReacting = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat")
	float LifeSpan = 5.f;

	void SetLevel(int32 InLevel) { Level = InLevel; }
	
protected:
	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo() override;
	virtual void InitializeDefaultAttributes() const override;
	virtual void StunTagChanged(const FGameplayTag CallbackTag, int32 NewCount) override;

	UPROPERTY(EditAnywhere, Category = "Combat")
	FName LeftHandSocketName;

	UPROPERTY(EditAnywhere, Category = "Combat")
	FName RightHandSocketName;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults")
	int32 Level = 1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UWidgetComponent> HealthBar;

	UPROPERTY(EditAnywhere, Category = "AI")
	TObjectPtr<UBehaviorTree> BehaviorTree;

	UPROPERTY()
	TObjectPtr<ADPAIController> DPAIController;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<ADPProjectileBase> ProjectileClass;
	
};
