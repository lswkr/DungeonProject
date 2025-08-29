// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstance/DPBaseAnimInstance.h"

#include "Character/DPCharacterBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UDPBaseAnimInstance::NativeInitializeAnimation()
{
	OwningCharacter = Cast<ADPCharacterBase>(TryGetPawnOwner());

	if (OwningCharacter)
	{
		OwningMovementComponent = OwningCharacter->GetCharacterMovement();
	}
}

void UDPBaseAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	if (!OwningCharacter || !OwningMovementComponent)
	{
		return;
	}

	GroundSpeed = OwningCharacter->GetVelocity().Size2D();

	const FTransform Transform = OwningCharacter->GetActorTransform();
	FVector Velocity = OwningCharacter->GetVelocity();
	FVector AngleVector = UKismetMathLibrary::InverseTransformDirection(Transform, Velocity);

	Angle = UKismetMathLibrary::MakeRotFromX(AngleVector).Yaw;

	bHasAcceleration = OwningMovementComponent->GetCurrentAcceleration().SizeSquared2D() > 0.f;
}
