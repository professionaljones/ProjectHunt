// Fill out your copyright notice in the Description page of Project Settings.


#include "HuntPlayerCharacter.h"

AHuntPlayerCharacter::AHuntPlayerCharacter()
{
	StatsComponent->MaxHealth = 200;
	StatsComponent->MaxAragon = 200;
	StatsComponent->CurrentHealth = StatsComponent->MaxHealth;
	StatsComponent->CurrentAragon = StatsComponent->MaxAragon;
	MaxStyleAmount = SSS_StyleLimit;
}

int32 AHuntPlayerCharacter::GetJumpCount()
{
	return JumpCount;
}

int32 AHuntPlayerCharacter::GetDashCount()
{
	return DashCount;
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

