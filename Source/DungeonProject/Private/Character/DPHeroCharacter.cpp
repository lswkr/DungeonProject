// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/DPHeroCharacter.h"

#include "DPGameplayTags.h"
#include "Player/DPPlayerState.h"
#include "AbilitySystem/DPAbilitySystemComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Actor/Items/DPWeaponBase.h"
#include "Components/BoxComponent.h"
#include "NiagaraComponent.h"
#include "AbilitySystem/Data/LevelUpInfo.h"
#include "Player/DPPlayerController.h"
#include "UI/HUD/DPHUD.h"


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

void ADPHeroCharacter::AddToXP_Implementation(int32 InXP)
{
	ADPPlayerState* DPPlayerState = GetPlayerState<ADPPlayerState>();
	check(DPPlayerState);
	DPPlayerState->AddToXP(InXP);
}


void ADPHeroCharacter::LevelUp_Implementation()
{
	MulticastLevelUpParticles();
}

int32 ADPHeroCharacter::GetXP_Implementation() const
{
	const ADPPlayerState* DPPlayerState = GetPlayerState<ADPPlayerState>();
	check(DPPlayerState);
	
	return DPPlayerState->GetXP();
}

int32 ADPHeroCharacter::FindLevelForXP_Implementation(int32 XP) const
{
	const ADPPlayerState* DPPlayerState = GetPlayerState<ADPPlayerState>();
	check(DPPlayerState);
	return DPPlayerState->LevelUpInfo->FindLevelForXP(XP);
}

int32 ADPHeroCharacter::GetAttributePointsReward_Implementation(int32 InLevel) const
{
	const ADPPlayerState* DPPlayerState = GetPlayerState<ADPPlayerState>();
	check(DPPlayerState);
	
	return DPPlayerState->LevelUpInfo->LevelUpInformation[InLevel].AttributePointReward;
}

int32 ADPHeroCharacter::GetSpellPointsReward_Implementation(int32 InLevel) const
{
	const ADPPlayerState* DPPlayerState = GetPlayerState<ADPPlayerState>();
	check(DPPlayerState);

	return DPPlayerState->LevelUpInfo->LevelUpInformation[InLevel].SpellPointReward;
}

void ADPHeroCharacter::AddToPlayerLevel_Implementation(int32 InPlayerLevel)
{
	ADPPlayerState* DPPlayerState = GetPlayerState<ADPPlayerState>();
	check(DPPlayerState);

	DPPlayerState->AddToLevel(InPlayerLevel);

	if (UDPAbilitySystemComponent* DPASC = Cast<UDPAbilitySystemComponent>(GetAbilitySystemComponent()))
	{
		DPASC->UpdateAbilityStatus(DPPlayerState->GetPlayerLevel());
	}
}

void ADPHeroCharacter::AddToSpellPoints_Implementation(int32 InSpellPoints)
{
	ADPPlayerState* DPPlayerState = GetPlayerState<ADPPlayerState>();
	check(DPPlayerState);

	DPPlayerState->AddToSpellPoints(InSpellPoints);
}

void ADPHeroCharacter::AddToAttributePoints_Implementation(int32 InAttributePoints)
{
	ADPPlayerState* DPPlayerState = GetPlayerState<ADPPlayerState>();
	check(DPPlayerState);

	DPPlayerState->AddToAttributePoints(InAttributePoints);
}

int32 ADPHeroCharacter::GetAttributePoints_Implementation() const
{
	ADPPlayerState* DPPlayerState = GetPlayerState<ADPPlayerState>();
	check(DPPlayerState);
	return DPPlayerState->GetAttributePoints();
}

int32 ADPHeroCharacter::GetSpellPoints_Implementation() const
{
	ADPPlayerState* DPPlayerState = GetPlayerState<ADPPlayerState>();
	check(DPPlayerState);
	return DPPlayerState->GetSpellPoints();
}

int32 ADPHeroCharacter::GetPlayerLevel_Implementation()
{
	const ADPPlayerState* DPPlayerState = GetPlayerState<ADPPlayerState>();
	check(DPPlayerState);
	return DPPlayerState->GetPlayerLevel();
}

void ADPHeroCharacter::ToggleCollision_Implementation(bool bShouldEnable)
{
	check(Weapon);

	if (bShouldEnable)
	{
		UE_LOG(LogTemp, Warning, TEXT("SetCollision Enabled"));
		Weapon->GetCollisionBoxComponent()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("SetCollision Unenabled"));
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

		FAttachmentTransformRules AttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, true);
		
		checkf(WeaponClass,TEXT("WeaponClass isn't selected in DPHeroCharacter. Please select WeaponClass."))

		Weapon = GetWorld()->SpawnActor<ADPWeaponBase>(WeaponClass, FVector::ZeroVector, FRotator::ZeroRotator,ActorSpawnParameters);
		Weapon->AttachToComponent(GetMesh(), AttachmentTransformRules, WeaponSocketName);

		Weapon->SetReplicates(true);
		Weapon->SetReplicateMovement(true);
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

	OnASCRegistered.Broadcast(AbilitySystemComponent);

	if (ADPPlayerController* DPPlayerController = Cast<ADPPlayerController>(GetController()))
	{
		if (ADPHUD* DPHUD = Cast<ADPHUD>(DPPlayerController->GetHUD()))
		{
			
		}
	}
}

void ADPHeroCharacter::MulticastLevelUpParticles_Implementation() const
{
	if (IsValid(LevelUpNiagaraComponent))
	{
		LevelUpNiagaraComponent->SetWorldLocation(GetActorLocation());
		LevelUpNiagaraComponent->Activate(true);
	}
}
