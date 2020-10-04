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
	return CurrentJumpCount;
}

int32 AHuntPlayerCharacter::GetDashCount()
{
	return CurrentDashCount;
}

bool AHuntPlayerCharacter::CanPlayerUseMissiles()
{
	return PlayerSavedStats.bHasMissileLauncher;
}

bool AHuntPlayerCharacter::CanPlayerUseAragon()
{
	return PlayerSavedStats.bUnlockedAragon;
}

bool AHuntPlayerCharacter::CanPlayerDash()
{
	return PlayerSavedStats.bUnlockedDash;
}

bool AHuntPlayerCharacter::CanPlayerWallrun()
{
	return PlayerSavedStats.bUnlockedWallrun;
}

void AHuntPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	MyPlayerController = Cast<AHuntPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	
}

void AHuntPlayerCharacter::UnlockAbility(bool AbilityToToggle, bool bUnlockAbility)
{
	AbilityToToggle = bUnlockAbility;
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
	if (CanPlayerUseMissiles())
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
	if (bAreMissilesEmpty == true)
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

void AHuntPlayerCharacter::UpdateMissileCapacity(int32 NewMissileAmount)
{
	MaxMissileCount = NewMissileAmount;
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

void AHuntPlayerCharacter::SetCurrentSuitPower(TEnumAsByte<ESuitMainAbilities> NewSuitPower)
{
	StatsComponent->CurrentSuitPower = NewSuitPower;
}

void AHuntPlayerCharacter::SetPowerModifierOne(TEnumAsByte<ESuitPowerModifiers> NewPowerModifier)
{
	StatsComponent->PowerModifierSlotOne = NewPowerModifier;
}

void AHuntPlayerCharacter::SetPowerModifierTwo(TEnumAsByte<ESuitPowerModifiers> NewPowerModifier)
{
	StatsComponent->PowerModifierSlotTwo = NewPowerModifier;
}

void AHuntPlayerCharacter::UpdateDashCount(int32 IncreaseAmount)
{
	MaxDashCount += IncreaseAmount;
	CurrentDashCount = MaxDashCount;

}

void AHuntPlayerCharacter::UpdateJumpCount(int32 IncreaseAmount)
{
	MaxJumpCount += IncreaseAmount;
	CurrentJumpCount = MaxDashCount;
}

void AHuntPlayerCharacter::SetPlayerStats(float NewMaxHealth, float NewMaxAragon, TEnumAsByte<EPlayerSuit> NewPlayerSuit, TEnumAsByte<ESuitMainAbilities> NewSuitPower, TEnumAsByte<ESuitPowerModifiers> NewPowerModifierOne, TEnumAsByte<ESuitPowerModifiers> NewPowerModifierTwo, int32 NewMaxMissileCount, FPlayerSaveableStats NewPlayerSaveableStats, TMap<int32, AHuntWeapon*> NewWeaponInventory, int32 NewCurrentDataPoints)
{
	StatsComponent->UpdateMaxHealth(NewMaxHealth);
	StatsComponent->UpdateMaxAragon(NewMaxAragon);
	SetPlayerSuit(NewPlayerSuit);
	SetCurrentSuitPower(NewSuitPower);
	SetPowerModifierOne(NewPowerModifierOne);
	SetPowerModifierTwo(NewPowerModifierTwo);
	UpdateMissileCapacity(NewMaxMissileCount);
	WeaponInventory = NewWeaponInventory;
	CurrentDataPoints = NewCurrentDataPoints;
	PlayerSavedStats = NewPlayerSaveableStats;
	IHuntCharacterInterface::Execute_UpdateStatsUI(this);
	
	
}

