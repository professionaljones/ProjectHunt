// Copyright 2020 Brandon Jones. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ProjectHunt/Character/Player/HuntPlayerCharacter.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "SaveGameInstanceSubsystem.generated.h"

/**
 *
 */
UCLASS()
class PROJECTHUNT_API USaveGameInstanceSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

protected:

	/*UPROPERTY(EditAnywhere)
		FPlayerSaveableStats SavedPlayerUnlockedStats;*/
	UPROPERTY(EditAnywhere)
		FPlayerMainAbilityData SavedQuicksilverAbilityStats;
	UPROPERTY(EditAnywhere)
		FPlayerMainAbilityData SavedShowstopperAbilityStats;
	UPROPERTY(EditAnywhere)
		FPlayerMainAbilityData SavedOverloadAbilityStats;
	UPROPERTY(EditAnywhere)
		FPlayerPowerModifierData SavedDashPowerStats;
	UPROPERTY(EditAnywhere)
		FPlayerPowerModifierData SavedBlastPowerStats;
	UPROPERTY(EditAnywhere)
		FWeaponStatsData SavedSavePistolStats;
	UPROPERTY(EditAnywhere)
		FWeaponStatsData SavedRifleStatsData;
	UPROPERTY(EditAnywhere)
		FWeaponStatsData SavedShotgunStatsData;
	UPROPERTY(EditAnywhere)
		FPlayerStatsData SavedPlayerStats;


public:

	

	//void SaveLoadData(FArchive& Ar, FPlayerSaveableStats& PlayerUnlockedStats, FPlayerMainAbilityData& QuicksilverAbilityStats, FPlayerMainAbilityData& ShowstopperAbilityStats, FPlayerMainAbilityData& OverloadAbilityStats, FPlayerPowerModifierData& DashPowerStats, FPlayerPowerModifierData& BlastPowerStats, FWeaponStatsData& SavePistolStats, FWeaponStatsData& SaveRifleStatsData, FWeaponStatsData& SaveShotgunStatsData, FPlayerStatsData& SavePlayerStats);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Save Slots")
		FString FirstSaveSlot = "SaveSlot01";

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Save Slots")
		FString CurrentSaveSlot;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = References)
		AHuntPlayerCharacter* PlayerCharacterReference;

public:


};
