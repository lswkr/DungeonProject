// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/DPCharacterBase.h"

// Sets default values
ADPCharacterBase::ADPCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADPCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADPCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ADPCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

