// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/DPPlayerController.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "DPGameplayTags.h"
#include "EnhancedInputSubsystems.h"
#include "NavigationPath.h"
#include "NavigationSystem.h"
#include "AbilitySystem/DPAbilitySystemComponent.h"
#include "Components/SplineComponent.h"
#include "Input/DPInputComponent.h"
#include "Interaction/HighlightInterface.h"
#include "NiagaraFunctionLibrary.h"


ADPPlayerController::ADPPlayerController()
{
	bReplicates = true;
	Spline = CreateDefaultSubobject<USplineComponent>("Spline");
}


void ADPPlayerController::BeginPlay()
{
	Super::BeginPlay();

	check(DPContext);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

	if (Subsystem)
	{
		Subsystem->AddMappingContext(DPContext, 0);
	}

	// bShowMouseCursor = true;
	// DefaultMouseCursor = EMouseCursor::Default;
	
	
}

void ADPPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UDPInputComponent* DPInputComponent = CastChecked<UDPInputComponent>(InputComponent);

	DPInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ADPPlayerController::Input_Move);
	DPInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ADPPlayerController::Input_Look);
	DPInputComponent->BindAction(ClickAction, ETriggerEvent::Started, this, &ADPPlayerController::InputPressed_RMB);
	DPInputComponent->BindAction(ClickAction, ETriggerEvent::Completed, this, &ADPPlayerController::InputReleased_RMB);
	DPInputComponent->BindAction(ClickAction, ETriggerEvent::Triggered, this, &ADPPlayerController::InputHeld_RMB);
	
	DPInputComponent->BindAbilityActions(InputConfig, this, &ThisClass::AbilityInputTagPressed, &ThisClass::AbilityInputTagReleased, &ThisClass::AbilityInputTagHeld);
}

void ADPPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	
	CursorTrace();
	AutoRun();
}


void ADPPlayerController::CursorTrace()
{
	
	if (GetASC() && GetASC()->HasMatchingGameplayTag(FDPGameplayTags::Get().Player_Block_CursorTrace))
	{
		UnhighlightActor(LastActor);
		UnhighlightActor(ThisActor);

		LastActor = nullptr;
		ThisActor = nullptr;
		return;
	}

	const ECollisionChannel TraceChannel = ECC_Visibility;
	GetHitResultUnderCursor(TraceChannel, false, CursorHit);
	if (!CursorHit.bBlockingHit) return;
	

	LastActor = ThisActor;
	if (IsValid(CursorHit.GetActor()) && CursorHit.GetActor()->Implements<UHighlightInterface>())
	{
		ThisActor = CursorHit.GetActor();
	}
	else
	{
		ThisActor = nullptr;
	}

	if (LastActor != ThisActor)
	{
		UnhighlightActor(LastActor);
		HighlightActor(ThisActor);
	}
	
}

void ADPPlayerController::AutoRun()
{
	if (!bAutoRunning) return;

	if (APawn* ControlledPawn = GetPawn())
	{
		const FVector LocationOnSpline = Spline->FindLocationClosestToWorldLocation(ControlledPawn->GetActorLocation(), ESplineCoordinateSpace::World);
		const FVector Direction = Spline->FindDirectionClosestToWorldLocation(LocationOnSpline, ESplineCoordinateSpace::World);
		ControlledPawn->AddMovementInput(Direction);

		const float DistanceToDestination = (LocationOnSpline - CachedDestination).Length();

		if (DistanceToDestination <= AutoRunAcceptanceRadius)
		{
			bAutoRunning = false;
		}

		//TODO: Targeting이면
	}
}

void ADPPlayerController::HighlightActor(AActor* InActor)
{
	if (IsValid(InActor) && InActor->Implements<UHighlightInterface>())
	{
		IHighlightInterface::Execute_HighlightActor(InActor);
	}
}

void ADPPlayerController::UnhighlightActor(AActor* InActor)
{
	if (IsValid(InActor) && InActor->Implements<UHighlightInterface>())
	{
		IHighlightInterface::Execute_UnhighlightActor(InActor);
	}
}

void ADPPlayerController::AbilityInputTagPressed(FGameplayTag InputTag)
{
	if (GetASC() && GetASC()->HasMatchingGameplayTag(FDPGameplayTags::Get().Player_Block_InputPressed))
	{
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("AbilityInputTagPressed Activating Tag: [%s]"),*InputTag.ToString());
	
	bAutoRunning = false;
	if (GetASC())
	{
		GetASC()->AbilityInputTagPressed(InputTag);
	}
}

void ADPPlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{
	
	if (GetASC() && GetASC()->HasMatchingGameplayTag(FDPGameplayTags::Get().Player_Block_InputReleased))
	{
		return;
	}
	
	UE_LOG(LogTemp, Warning, TEXT("AbilityInputTagReleased"));
	if (GetASC())
	{
		GetASC()->AbilityInputTagReleased(InputTag);
	}

	if (TargetingStatus != ETargetingStatus::TargetingEnemy)
	{
		
		TargetingStatus = ETargetingStatus::NotTargeting;
	}
	
}

void ADPPlayerController::AbilityInputTagHeld(FGameplayTag InputTag)
{
	if (GetASC() && GetASC()->HasMatchingGameplayTag(FDPGameplayTags::Get().Player_Block_InputHeld))
	{
		return;
	}
	
	UE_LOG(LogTemp, Warning, TEXT("AbilityInputTagHeld Activating, Tag: [%s]"),*InputTag.ToString());
	
}

UDPAbilitySystemComponent* ADPPlayerController::GetASC()
{
	if (DPAbilitySystemComponent == nullptr)
	{
		DPAbilitySystemComponent = Cast<UDPAbilitySystemComponent> (UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn<APawn>()));
	}
	return DPAbilitySystemComponent;
}

void ADPPlayerController::Input_Move(const FInputActionValue& InputActionValue)
{
	bAutoRunning = false; //키보드로 움직이는 순간 AutoRun 멈추도록

	const FVector2D MovementVector = InputActionValue.Get<FVector2D>();
	const FRotator MovementRotation(0.f, this->GetControlRotation().Yaw, 0.f);

	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		if (MovementVector.Y != 0.f)
		{
			const FVector ForwardDirection =MovementRotation.RotateVector(FVector::ForwardVector);
			ControlledPawn->AddMovementInput(ForwardDirection, MovementVector.Y);
		}
		if (MovementVector.X != 0.f)
		{
			const FVector RightDirection = MovementRotation.RotateVector(FVector::RightVector);
			ControlledPawn->AddMovementInput(RightDirection, MovementVector.X);
		}
	}
	
	
}

void ADPPlayerController::Input_Look(const FInputActionValue& InputActionValue)
{
	const FVector2D LookAxisVector = InputActionValue.Get<FVector2D>();
	UE_LOG(LogTemp, Warning, TEXT("Input_Look Activating"));
	if (APawn* ControlledPawn = GetPawn<APawn>())
	{	
		if (LookAxisVector.X != 0.f)
		{
			ControlledPawn->AddControllerYawInput(LookAxisVector.X);
		}
	}
}

void ADPPlayerController::InputPressed_RMB(const FInputActionValue& InputActionValue)
{
	
}

void ADPPlayerController::InputHeld_RMB(const FInputActionValue& InputActionValue)
{
	FollowTime += GetWorld()->GetDeltaSeconds();
	if (CursorHit.bBlockingHit)
	{
		CachedDestination = CursorHit.ImpactPoint;
	}

	if (APawn* ControlledPawn = GetPawn())
	{
		const FVector WorldDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
		ControlledPawn->AddMovementInput(WorldDirection);
	}
}

void ADPPlayerController::InputReleased_RMB(const FInputActionValue& InputActionValue)
{
	const APawn* ControlledPawn = GetPawn();
	if (FollowTime <= ShortPressThreshold && ControlledPawn)
	{
		if (GetASC() && !GetASC()->HasMatchingGameplayTag(FDPGameplayTags::Get().Player_Block_InputPressed))
		{
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(this,ClickNiagaraSystem, CachedDestination);
		}
		if (UNavigationPath* NavPath = UNavigationSystemV1::FindPathToLocationSynchronously(this, ControlledPawn->GetActorLocation(), CachedDestination))
		{
			Spline->ClearSplinePoints();

			for (const FVector& PointLocation : NavPath->PathPoints)
			{
				Spline->AddSplinePoint(PointLocation, ESplineCoordinateSpace::World);
			}
			if (NavPath->PathPoints.Num() > 0)
			{
				CachedDestination = NavPath->PathPoints[NavPath->PathPoints.Num()-1];
				bAutoRunning = true;
			}
		}
	}

	FollowTime = 0;
}
