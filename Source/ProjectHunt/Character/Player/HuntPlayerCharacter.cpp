// Fill out your copyright notice in the Description page of Project Settings.


#include "HuntPlayerCharacter.h"

AHuntPlayerCharacter::AHuntPlayerCharacter()
{
	StatsComponent->MaxHealth = 200;
	StatsComponent->MaxAragon = 200;
	StatsComponent->CurrentHealth = StatsComponent->MaxHealth;
	StatsComponent->CurrentAragon = StatsComponent->MaxAragon;
	StatsComponent->AragonRechargeAmount = 15.0f;
	MaxStyleAmount = SSS_StyleLimit;

	//Create a secondary AudioComponent 
	SuitAudioComponent = CreateDefaultSubobject<UAudioComponent>("SuitAudioComponent");
	MovementSpeed = 1300.0f;
}

int32 AHuntPlayerCharacter::GetJumpCount()
{
	return JumpCount;
}

int32 AHuntPlayerCharacter::GetDashCount()
{
	return DashCount;
}

bool AHuntPlayerCharacter::CanPlayerUseMissiles()
{
	return bHasMissileLauncher;
}

void AHuntPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	MyPlayerController = Cast<AHuntPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	
}

void AHuntPlayerCharacter::UnlockAbility(bool bUnlockAbility)
{
	bUnlockAbility = true;
}

int32 AHuntPlayerCharacter::GetCurrentMissiles()
{
	UI_CurrentMissileCount = CurrentMissileCount;
	return UI_CurrentMissileCount;
}

int32 AHuntPlayerCharacter::GetMaxMissiles()
{
	UI_MaxMissileCount = MaxMissileCount;
	return UI_MaxMissileCount;
}

void AHuntPlayerCharacter::ConsumeMissiles(int32 ConsumeMissileAmount)
{
	if (bHasMissileLauncher)
	{
		if (!bAreMissilesEmpty)
		{
			CurrentMissileCount -= ConsumeMissileAmount;
			if (CurrentMissileCount <= 0)
			{
				bAreMissilesEmpty = true;
				CurrentMissileCount = 0;
			}
		}
	}


}

void AHuntPlayerCharacter::RecoverMissiles(int32 RecoverAmount)
{
	CurrentMissileCount += RecoverAmount;
	if (bAreMissilesEmpty == false)
	{
		bAreMissilesEmpty = false;
	}
	if (CurrentMissileCount >= MaxMissileCount)
	{
		CurrentMissileCount = MaxMissileCount;

	}
}

void AHuntPlayerCharacter::UpgradeMissileCapacity(int32 IncreaseAmount)
{
	MaxMissileCount = MaxMissileCount + IncreaseAmount;
	CurrentMissileCount = MaxMissileCount;
}

void AHuntPlayerCharacter::SetPlayerSuit(TEnumAsByte<EPlayerSuit> NewPlayerSuit)
{
	switch (CurrentPlayerSuit)
	{
	case EPlayerSuit::Suit_Standard:
	
		DamageDefenseModifer = 0.0f;
	
	case EPlayerSuit::Suit_Version2:
	
		DamageDefenseModifer = 0.15f;
	
	case EPlayerSuit::Suit_Version3:
	
		DamageDefenseModifer = 0.30f;
	
	case EPlayerSuit::Suit_Version4:
	
		DamageDefenseModifer = 0.50f;
	
	default:
		break;
	
	}
}


