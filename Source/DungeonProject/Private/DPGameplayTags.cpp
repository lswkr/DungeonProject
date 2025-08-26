// Fill out your copyright notice in the Description page of Project Settings.


#include "DPGameplayTags.h"
#include "GameplayTagsManager.h"
FDPGameplayTags FDPGameplayTags::GameplayTags;

void FDPGameplayTags::InitializeNativeGameplayTags()
{

	/* Player Tags */
	GameplayTags.Player_Block_InputPressed = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Player.Block.InputPressed"),
		FString("Block Input Pressed Callback for Input")
		);
	
	GameplayTags.Player_Block_InputReleased = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Player.Block.InputReleased"),
		FString("Block Input Released Callback for Input")
		);
	
	GameplayTags.Player_Block_InputHeld = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Player.Block.InputHeld"),
		FString("Block Input Held Callback for Input")
		);

	GameplayTags.Player_Block_CursorTrace = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Player.Block.CursorTrace"),
		FString("Block CursorTrace Callback for Input")
		);


	
	GameplayTags.Abilities_Status_Equipped = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.Status.Equipped"),
		FString("Equipped Status")
		);

	
	/* Primary Attributes */
	GameplayTags.Attributes_Primary_Strength = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.Strength"),
		FString("Increase MaxHP and Attack Power")
		);
	
	GameplayTags.Attributes_Primary_Intelligence = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.Intelligence"),
		FString("Increase MaxMP and Magic Power")
		);
	
	GameplayTags.Attributes_Primary_Luck = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.Luck"),
		FString("Increase Critical Hit Chance and Block Chance")
		);

	GameplayTags.Attributes_Primary_Will = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.Will"),
		FString("Increase Defense Power and Amount of Health/Mana Regenerated")
		);

	
	/* Secondary Attributes */
	GameplayTags.Attributes_Secondary_Attack = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Attributes.Secondary.Attack"),
	FString("Attack Power")
	);
	
	GameplayTags.Attributes_Secondary_Defense = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Attributes.Secondary.Defense"),
	FString("Defense Power")
	);

	GameplayTags.Attributes_Secondary_CriticalHitChance = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Attributes.Secondary.CriticalHitChance"),
	FString("Chance to Increase Damage")
	);

	GameplayTags.Attributes_Secondary_BlockChance = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Attributes.Secondary.BlockChance"),
	FString("Chance to Block")
	);

	GameplayTags.Attributes_Secondary_HealthRegeneration = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Attributes.Secondary.HealthRegeneration"),
	FString("Amount of Health Regenerated Every 1 Second")
	);

	GameplayTags.Attributes_Secondary_ManaRegeneration = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Attributes.Secondary.ManaRegeneration"),
	FString("Amount of Mana Regenerated Every 1 Second")
	);

	
	/* Vital Attributes */
	GameplayTags.Attributes_Vital_MaxHealth = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Attributes.Vital.MaxHealth"),
	FString("Maximum Amount of Health Obtainable")
	);

	GameplayTags.Attributes_Vital_MaxMana = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Attributes.Vital.MaxMana"),
	FString("Maximum Amount of Mana Obtainable")
	);

	GameplayTags.Attributes_Vital_Health = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Attributes.Vital.Health"),
	FString("Amount of Current Health")
	);

	GameplayTags.Attributes_Vital_Mana = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Attributes.Vital.Mana"),
	FString("Amount of Current Mana")
	);
}
