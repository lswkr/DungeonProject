// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/DPPlayerController.h"


#include "Components/SplineComponent.h"
#include "Interaction/HighlightInterface.h"

ADPPlayerController::ADPPlayerController()
{
	bReplicates = true;
	Spline = CreateDefaultSubobject<USplineComponent>("Spline");
}


void ADPPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void ADPPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
}

void ADPPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	
	CursorTrace();
	AutoRun();
}


void ADPPlayerController::CursorTrace()
{
	
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
}

void ADPPlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{
}

void ADPPlayerController::AbilityInputTagHeld(FGameplayTag InputTag)
{
}
void ADPPlayerController::Input_Move(const FInputActionValue& InputActionValue)
{
	bAutoRunning = false; //키보드로 움직이는 순간 AutoRun 멈추도록
	
}