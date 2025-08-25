// Fill out your copyright notice in the Description page of Project Settings.


#include "DPGameplayTags.h"
#include "GameplayTagsManager.h"
FDPGameplayTags FDPGameplayTags::GameplayTags;

void FDPGameplayTags::InitializeNativeGameplayTags()
{
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

	/*FGameplayTag ;
	FGameplayTag ;
	FGameplayTag ;*/
}
