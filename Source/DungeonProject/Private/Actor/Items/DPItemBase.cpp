// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Items/DPItemBase.h"

// Sets default values
ADPItemBase::ADPItemBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADPItemBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADPItemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

