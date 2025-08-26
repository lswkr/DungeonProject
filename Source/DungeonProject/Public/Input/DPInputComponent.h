// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DPInputConfig.h"
#include "EnhancedInputComponent.h"
#include "DPInputComponent.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONPROJECT_API UDPInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:
	template<class UserClass, typename PressedFuncType, typename ReleasedFuncType, typename HeldFuncType>
	void BindAbilityActions(const UDPInputConfig* InputConfig, UserClass* Object, PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc, HeldFuncType HeldFunc);
	
};

template <class UserClass, typename PressedFuncType, typename ReleasedFuncType, typename HeldFuncType>
void UDPInputComponent::BindAbilityActions(const UDPInputConfig* InputConfig, UserClass* Object,
	PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc, HeldFuncType HeldFunc)
{
	check(InputConfig);
	
	for (const FDPInputAction& Action : InputConfig->AbilityInputActions)
	{
		if (Action.InputAction && Action.InputTag.IsValid())
		{
			if (PressedFunc)
			{
				BindAction(Action.InputAction, Object, ETriggerEvent::Started, PressedFunc);
			}
			if (ReleasedFunc)
			{
				BindAction(Action.InputAction, Object, ETriggerEvent::Completed, ReleasedFunc);
			}

			if (HeldFunc)
			{
				BindAction(Action.InputAction, Object, ETriggerEvent::Triggered, HeldFunc);
			}


		}

		
	}
}
