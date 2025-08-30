// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/DPHeroCharacter.h"

#include "Player/DPPlayerState.h"
#include "AbilitySystem/DPAbilitySystemComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Actor/Items/DPWeaponBase.h"
#include "Components/BoxComponent.h"


ADPHeroCharacter::ADPHeroCharacter()
{
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->bUsePawnControlRotation = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);;
	Camera->bUsePawnControlRotation = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 500.f, 0.f);
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
}

void ADPHeroCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	InitAbilityActorInfo();
}

void ADPHeroCharacter::OnRep_PlayerState()
{
	InitAbilityActorInfo();
}

void ADPHeroCharacter::ToggleCollision_Implementation(bool bShouldEnable)
{
	check(Weapon);

	if (bShouldEnable)
	{
		Weapon->GetCollisionBoxComponent()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	}
	else
	{
		Weapon->GetCollisionBoxComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	
}

void ADPHeroCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	GetMesh()->HideBoneByName(TEXT("sword_bottom"), EPhysBodyOp::PBO_None);//스워드 및 방패 숨기기
	GetMesh()->HideBoneByName(TEXT("sword_top"), EPhysBodyOp::PBO_None);//스워드 및 방패 숨기기

	if(HasAuthority())
	{
		FActorSpawnParameters ActorSpawnParameters;
		ActorSpawnParameters.Owner = this;
		ActorSpawnParameters.Instigator = Cast<APawn>(this);
		ActorSpawnParameters.SpawnCollisionHandlingOverride =  ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		ActorSpawnParameters.TransformScaleMethod = ESpawnActorScaleMethod::MultiplyWithRoot;

		FAttachmentTransformRules AttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::KeepRelative, EAttachmentRule::KeepWorld, true);
		
		checkf(WeaponClass,TEXT("WeaponClass isn't selected in DPHeroCharacter. Please select WeaponClass."))

		Weapon = GetWorld()->SpawnActor<ADPWeaponBase>(WeaponClass, FVector::ZeroVector, FRotator::ZeroRotator,ActorSpawnParameters);
		Weapon->AttachToComponent(GetMesh(), AttachmentTransformRules, WeaponSocketName);
		
		
	}
	

}

void ADPHeroCharacter::InitAbilityActorInfo()
{
	ADPPlayerState* DPPlayerState = GetPlayerState<ADPPlayerState>();
	check(DPPlayerState);

	DPPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(DPPlayerState, this);
	Cast<UDPAbilitySystemComponent> (DPPlayerState->GetAbilitySystemComponent())->AbilityActorInfoSet();

	AbilitySystemComponent = DPPlayerState->GetAbilitySystemComponent();
	AttributeSet = DPPlayerState->GetAttributeSet();
}
