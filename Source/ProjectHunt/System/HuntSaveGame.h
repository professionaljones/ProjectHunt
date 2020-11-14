// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "ProjectHunt/Character/HuntStatsComponent.h"
#include "ProjectHunt/Weapons/HuntWeapon.h"
#include "ProjectHunt/Character/Player/HuntPlayerCharacter.h"
#include "Serialization/ObjectAndNameAsStringProxyArchive.h"
#include "Serialization/Archive.h"
#include "HuntSaveGame.generated.h"

struct FHuntSaveGameArchive : public FObjectAndNameAsStringProxyArchive
{
	FHuntSaveGameArchive(FArchive& InInnerArchive) : FObjectAndNameAsStringProxyArchive(InInnerArchive, true)
	{
		ArIsSaveGame = true;
		// Optional, useful when saving/loading variables without resetting the level.
		// Serialize variables even if weren't modified and maintain their default values.
		ArNoDelta = false;
	}
};
USTRUCT(BlueprintType)
struct FHuntPlayerStatsData : public FTableRowBase
{

	GENERATED_USTRUCT_BODY()

	UPROPERTY(VisibleAnywhere, Category = "Player|Stats")
		FPlayerSaveableStats SavedPlayerUnlockedAbilities;

	UPROPERTY(VisibleAnywhere, Category = "Player|Stats")
		float SavedCurrentPlayerHealth;

	UPROPERTY(VisibleAnywhere, Category = "Player|Stats")
		float SavedMaxPlayerHealth;

	UPROPERTY(VisibleAnywhere, Category = "Player|Stats")
		float SavedCurrentPlayerAragon;

	UPROPERTY(VisibleAnywhere, Category = "Player|Stats")
		float SavedMaxPlayerAragon;

	UPROPERTY(VisibleAnywhere, Category = "Player|Transform")
		FTransform SavedPlayerTransform;

	UPROPERTY(VisibleAnywhere, Category = "Player|Stats")
		float SavedPlayerItemPercentage;

	UPROPERTY(VisibleAnywhere, Category = "Player|Stats")
		float SavedPlayerCurrentDP;

	UPROPERTY(VisibleAnywhere, Category = "Player|Stats")
		EPlayerSuit SavedCurrentSuit;

	UPROPERTY(VisibleAnywhere, Category = "Player|Stats")
		ESuitPowerModifiers SavedPowerModifierOne;

	UPROPERTY(VisibleAnywhere, Category = "Player|Stats")
		ESuitPowerModifiers SavedPowerModifierTwo;
};
USTRUCT(BlueprintType)
struct FHuntPlayerWeaponStatsData : public FTableRowBase
{

	GENERATED_USTRUCT_BODY()

	UPROPERTY(VisibleAnywhere, Category = "Player|Inventory")
		TMap<int, class AHuntWeapon*> SavedPlayerInventory;

	UPROPERTY(VisibleAnywhere, Category = "Player|Inventory")
		FWeaponStatsData SavedPistolStats;

	UPROPERTY(VisibleAnywhere, Category = "Player|Inventory")
		FWeaponStatsData SavedRifleStats;

	UPROPERTY(VisibleAnywhere, Category = "Player|Inventory")
		FWeaponStatsData SavedShotgunStats;
};
USTRUCT(BlueprintType)
struct FHuntSavedGameData : public FTableRowBase
{

	GENERATED_USTRUCT_BODY()

	UPROPERTY(VisibleAnywhere, Category = "Game")
		FString SavedCurrentLevelName;

	UPROPERTY(VisibleAnywhere, Category = "Game")
		FTimespan SavedCurrentPlayTime;


	UPROPERTY(VisibleAnywhere, Category = "Game")
		FString CurrentManualSaveSlotName;

	
};
/**
 *
 */
UCLASS()
class PROJECTHUNT_API UHuntSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UHuntSaveGame();

	//FArchive is shared base class for FBufferArchive and FMemoryReader
	//void SaveLoadData(FArchive& Ar, int32& SaveDataInt32, FVector& SaveDataVector, TArray<FRotator>& SaveDataRotatorArray);
	void SaveLoadData(FArchive& Ar, FHuntPlayerStatsData& SaveDataPlayerStats, FHuntPlayerWeaponStatsData& SaveDataPlayerInventory, FHuntSavedGameData& SaveDataGameStats);
	void SaveLoadData_2(FArchive& Ar, float SaveCurrentPlayerHealth, float SaveMaxPlayerHealth, float SaveCurrentPlayerAragon, float SaveMaxPlayerAragon);

	UPROPERTY(VisibleAnywhere, Category = Basic)
		FString SaveSlotName;

	UPROPERTY(VisibleAnywhere, Category = Basic)
		FString PlayerName;

	UPROPERTY(VisibleAnywhere, Category = Basic)
		uint32 UserIndex;

	UPROPERTY(VisibleAnywhere, Category = "Save Data|Player")
		FHuntPlayerStatsData SavedPlayerStats;

	UPROPERTY(VisibleAnywhere, Category = "Save Data|Inventory")
		FHuntPlayerWeaponStatsData SavedPlayerInventory;

	UPROPERTY(VisibleAnywhere, Category = "Save Data|Game")
		FHuntSavedGameData SavedPlayerGameData;

	bool SaveGameDataToFile(const FString& FullFilePath);
	bool LoadGameDataToFile(const FString& FullFilePath, FHuntPlayerStatsData& SaveDataPlayerStats, FHuntPlayerWeaponStatsData& SaveDataPlayerInventory, FHuntSavedGameData& SaveDataGameStats);

private:
	
public:

	//FBufferArchive ArchiveToWrite;

	/*FORCEINLINE FArchive &operator<<(FArchive &Ar, FHuntPlayerWeaponStatsData& SavedWeaponStatsStruct)
	{
		Ar << SavedWeaponStatsStruct.SavedPistolStats;

		return Ar;
	}*/
	friend FArchive& operator<<(FArchive& Ar, UHuntSaveGame& SaveGameData)
	{
		Ar << SaveGameData.SavedPlayerStats.SavedCurrentPlayerHealth;
		Ar << SaveGameData.SavedPlayerStats.SavedMaxPlayerHealth;
		Ar << SaveGameData.SavedPlayerStats.SavedCurrentPlayerAragon;
		Ar << SaveGameData.SavedPlayerStats.SavedMaxPlayerAragon;
		Ar << SaveGameData.SavedPlayerStats.SavedPlayerTransform;
		Ar << SaveGameData.SavedPlayerStats.SavedPlayerItemPercentage;
		Ar << SaveGameData.SavedPlayerStats.SavedPlayerCurrentDP;
		Ar << SaveGameData.SavedPlayerStats.SavedPlayerUnlockedAbilities.bHasMissileLauncher;
		Ar << SaveGameData.SavedPlayerStats.SavedPlayerUnlockedAbilities.bUnlockedAragon;
		Ar << SaveGameData.SavedPlayerStats.SavedPlayerUnlockedAbilities.bUnlockedDash;
		Ar << SaveGameData.SavedPlayerStats.SavedPlayerUnlockedAbilities.bUnlockedWallrun;
		Ar << SaveGameData.SavedPlayerStats.SavedCurrentSuit;
		Ar << SaveGameData.SavedPlayerStats.SavedPowerModifierOne;
		Ar << SaveGameData.SavedPlayerStats.SavedPowerModifierTwo;
		Ar << SaveGameData.SavedPlayerInventory.SavedPistolStats.BaseDamage;
		Ar << SaveGameData.SavedPlayerInventory.SavedPistolStats.DamageMultiplierAmount;
		Ar << SaveGameData.SavedPlayerInventory.SavedPistolStats.DamageModifierAmount;
		Ar << SaveGameData.SavedPlayerInventory.SavedPistolStats.ChargeRate;
		Ar << SaveGameData.SavedPlayerInventory.SavedPistolStats.ChargeLimitLevel;
		Ar << SaveGameData.SavedPlayerInventory.SavedPistolStats.ChargeRateLevel;
		Ar << SaveGameData.SavedPlayerInventory.SavedPistolStats.WeaponChargeDelay;
		Ar << SaveGameData.SavedPlayerInventory.SavedPistolStats.CriticalHitDamage;
		Ar << SaveGameData.SavedPlayerInventory.SavedPistolStats.CriticalHitMultiplier;
		Ar << SaveGameData.SavedPlayerInventory.SavedPistolStats.FireRate;
		Ar << SaveGameData.SavedPlayerInventory.SavedPistolStats.MaxWeaponLevel;
		Ar << SaveGameData.SavedPlayerInventory.SavedPistolStats.OriginalBaseDamageAmount;
		Ar << SaveGameData.SavedPlayerInventory.SavedPistolStats.OriginalDamageModifier;
		Ar << SaveGameData.SavedPlayerInventory.SavedPistolStats.OriginalDamageMultiplier;

		Ar << SaveGameData.SavedPlayerInventory.SavedRifleStats.BaseDamage;
		Ar << SaveGameData.SavedPlayerInventory.SavedRifleStats.DamageMultiplierAmount;
		Ar << SaveGameData.SavedPlayerInventory.SavedRifleStats.DamageModifierAmount;
		Ar << SaveGameData.SavedPlayerInventory.SavedRifleStats.ChargeRate;
		Ar << SaveGameData.SavedPlayerInventory.SavedRifleStats.ChargeLimitLevel;
		Ar << SaveGameData.SavedPlayerInventory.SavedRifleStats.ChargeRateLevel;
		Ar << SaveGameData.SavedPlayerInventory.SavedRifleStats.WeaponChargeDelay;
		Ar << SaveGameData.SavedPlayerInventory.SavedRifleStats.CriticalHitDamage;
		Ar << SaveGameData.SavedPlayerInventory.SavedRifleStats.CriticalHitMultiplier;
		Ar << SaveGameData.SavedPlayerInventory.SavedRifleStats.FireRate;
		Ar << SaveGameData.SavedPlayerInventory.SavedRifleStats.MaxWeaponLevel;
		Ar << SaveGameData.SavedPlayerInventory.SavedRifleStats.OriginalBaseDamageAmount;
		Ar << SaveGameData.SavedPlayerInventory.SavedRifleStats.OriginalDamageModifier;
		Ar << SaveGameData.SavedPlayerInventory.SavedRifleStats.OriginalDamageMultiplier;
		Ar << SaveGameData.SavedPlayerInventory.SavedRifleStats.WeaponDamageLevel;

		Ar << SaveGameData.SavedPlayerInventory.SavedShotgunStats.BaseDamage;
		Ar << SaveGameData.SavedPlayerInventory.SavedShotgunStats.DamageMultiplierAmount;
		Ar << SaveGameData.SavedPlayerInventory.SavedShotgunStats.DamageModifierAmount;
		Ar << SaveGameData.SavedPlayerInventory.SavedShotgunStats.ChargeRate;
		Ar << SaveGameData.SavedPlayerInventory.SavedShotgunStats.ChargeLimitLevel;
		Ar << SaveGameData.SavedPlayerInventory.SavedShotgunStats.ChargeRateLevel;
		Ar << SaveGameData.SavedPlayerInventory.SavedShotgunStats.WeaponChargeDelay;
		Ar << SaveGameData.SavedPlayerInventory.SavedShotgunStats.CriticalHitDamage;
		Ar << SaveGameData.SavedPlayerInventory.SavedShotgunStats.CriticalHitMultiplier;
		Ar << SaveGameData.SavedPlayerInventory.SavedShotgunStats.FireRate;
		Ar << SaveGameData.SavedPlayerInventory.SavedShotgunStats.MaxWeaponLevel;
		Ar << SaveGameData.SavedPlayerInventory.SavedShotgunStats.OriginalBaseDamageAmount;
		Ar << SaveGameData.SavedPlayerInventory.SavedShotgunStats.OriginalDamageModifier;
		Ar << SaveGameData.SavedPlayerInventory.SavedShotgunStats.OriginalDamageMultiplier;
		Ar << SaveGameData.SavedPlayerInventory.SavedShotgunStats.WeaponDamageLevel;

		Ar << SaveGameData.SavedPlayerGameData.SavedCurrentPlayTime;
		Ar << SaveGameData.SavedPlayerGameData.SavedCurrentLevelName;
		Ar << SaveGameData.SavedPlayerGameData.CurrentManualSaveSlotName;
		return Ar;
		
	}

};
