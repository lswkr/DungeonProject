// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Items/DPWeaponBase.h"
#include "Components/BoxComponent.h"
#include "Components/SkeletalMeshComponent.h"

ADPWeaponBase::ADPWeaponBase()
{
	BoxComponent = CreateDefaultSubobject<UBoxComponent>("BoxComponent");
	SetRootComponent(BoxComponent);
	BoxComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMeshComponent");
	SkeletalMeshComponent->SetupAttachment(GetRootComponent());
	SkeletalMeshComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	
}

void ADPWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ADPWeaponBase::OnHit);
}

void ADPWeaponBase::OnHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor==GetOwner()) return;
	
	UE_LOG(LogTemp, Warning, TEXT("HIT! (from ADPWeaponBase::OnHit"));
}
