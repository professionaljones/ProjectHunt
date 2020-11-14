// Fill out your copyright notice in the Description page of Project Settings.


#include "HuntSaveGame.h"
#include "Serialization/MemoryReader.h"
#include "HAL/FileManager.h"
#include "Serialization/MemoryWriter.h"
#include "Engine/World.h"

UHuntSaveGame::UHuntSaveGame()
{
	SaveSlotName = TEXT("TestSaveSlot");
	UserIndex = 0;
}

void UHuntSaveGame::SaveLoadData(FArchive& Ar, FHuntPlayerStatsData& SaveDataPlayerStats, FHuntPlayerWeaponStatsData& SaveDataPlayerInventory, FHuntSavedGameData& SaveDataGameStats)
{

	Ar << SaveDataPlayerStats.SavedCurrentPlayerHealth;
	Ar << SaveDataPlayerStats.SavedMaxPlayerHealth;
	Ar << SaveDataPlayerStats.SavedCurrentPlayerAragon;
	Ar << SaveDataPlayerStats.SavedMaxPlayerAragon;
	Ar << SaveDataPlayerStats.SavedPlayerTransform;
	Ar << SaveDataPlayerStats.SavedPlayerItemPercentage;
	Ar << SaveDataPlayerStats.SavedPlayerCurrentDP;
	Ar << SaveDataPlayerStats.SavedPlayerUnlockedAbilities.bHasMissileLauncher;
	Ar << SaveDataPlayerStats.SavedPlayerUnlockedAbilities.bUnlockedAragon;
	Ar << SaveDataPlayerStats.SavedPlayerUnlockedAbilities.bUnlockedDash;
	Ar << SaveDataPlayerStats.SavedPlayerUnlockedAbilities.bUnlockedWallrun;
	Ar << SaveDataPlayerStats.SavedCurrentSuit;
	Ar << SaveDataPlayerStats.SavedPowerModifierOne;
	Ar << SaveDataPlayerStats.SavedPowerModifierTwo;
	Ar << SaveDataPlayerInventory.SavedPistolStats.BaseDamage;
	Ar << SaveDataPlayerInventory.SavedPistolStats.DamageMultiplierAmount;
	Ar << SaveDataPlayerInventory.SavedPistolStats.DamageModifierAmount;
	Ar << SaveDataPlayerInventory.SavedPistolStats.ChargeRate;
	Ar << SaveDataPlayerInventory.SavedPistolStats.ChargeLimitLevel;
	Ar << SaveDataPlayerInventory.SavedPistolStats.ChargeRateLevel;
	Ar << SaveDataPlayerInventory.SavedPistolStats.WeaponChargeDelay;
	Ar << SaveDataPlayerInventory.SavedPistolStats.CriticalHitDamage;
	Ar << SaveDataPlayerInventory.SavedPistolStats.CriticalHitMultiplier;
	Ar << SaveDataPlayerInventory.SavedPistolStats.FireRate;
	Ar << SaveDataPlayerInventory.SavedPistolStats.MaxWeaponLevel;
	Ar << SaveDataPlayerInventory.SavedPistolStats.OriginalBaseDamageAmount;
	Ar << SaveDataPlayerInventory.SavedPistolStats.OriginalDamageModifier;
	Ar << SaveDataPlayerInventory.SavedPistolStats.OriginalDamageMultiplier;

	Ar << SaveDataPlayerInventory.SavedRifleStats.BaseDamage;
	Ar << SaveDataPlayerInventory.SavedRifleStats.DamageMultiplierAmount;
	Ar << SaveDataPlayerInventory.SavedRifleStats.DamageModifierAmount;
	Ar << SaveDataPlayerInventory.SavedRifleStats.ChargeRate;
	Ar << SaveDataPlayerInventory.SavedRifleStats.ChargeLimitLevel;
	Ar << SaveDataPlayerInventory.SavedRifleStats.ChargeRateLevel;
	Ar << SaveDataPlayerInventory.SavedRifleStats.WeaponChargeDelay;
	Ar << SaveDataPlayerInventory.SavedRifleStats.CriticalHitDamage;
	Ar << SaveDataPlayerInventory.SavedRifleStats.CriticalHitMultiplier;
	Ar << SaveDataPlayerInventory.SavedRifleStats.FireRate;
	Ar << SaveDataPlayerInventory.SavedRifleStats.MaxWeaponLevel;
	Ar << SaveDataPlayerInventory.SavedRifleStats.OriginalBaseDamageAmount;
	Ar << SaveDataPlayerInventory.SavedRifleStats.OriginalDamageModifier;
	Ar << SaveDataPlayerInventory.SavedRifleStats.OriginalDamageMultiplier;
	Ar << SaveDataPlayerInventory.SavedRifleStats.WeaponDamageLevel;

	Ar << SaveDataPlayerInventory.SavedShotgunStats.BaseDamage;
	Ar << SaveDataPlayerInventory.SavedShotgunStats.DamageMultiplierAmount;
	Ar << SaveDataPlayerInventory.SavedShotgunStats.DamageModifierAmount;
	Ar << SaveDataPlayerInventory.SavedShotgunStats.ChargeRate;
	Ar << SaveDataPlayerInventory.SavedShotgunStats.ChargeLimitLevel;
	Ar << SaveDataPlayerInventory.SavedShotgunStats.ChargeRateLevel;
	Ar << SaveDataPlayerInventory.SavedShotgunStats.WeaponChargeDelay;
	Ar << SaveDataPlayerInventory.SavedShotgunStats.CriticalHitDamage;
	Ar << SaveDataPlayerInventory.SavedShotgunStats.CriticalHitMultiplier;
	Ar << SaveDataPlayerInventory.SavedShotgunStats.FireRate;
	Ar << SaveDataPlayerInventory.SavedShotgunStats.MaxWeaponLevel;
	Ar << SaveDataPlayerInventory.SavedShotgunStats.OriginalBaseDamageAmount;
	Ar << SaveDataPlayerInventory.SavedShotgunStats.OriginalDamageModifier;
	Ar << SaveDataPlayerInventory.SavedShotgunStats.OriginalDamageMultiplier;
	Ar << SaveDataPlayerInventory.SavedShotgunStats.WeaponDamageLevel;

	Ar << SaveDataGameStats.SavedCurrentPlayTime;
	Ar << SaveDataGameStats.SavedCurrentLevelName;
	Ar << SaveDataGameStats.CurrentManualSaveSlotName;
	SavedPlayerStats = SaveDataPlayerStats;
	SavedPlayerInventory = SaveDataPlayerInventory;
	SavedPlayerGameData = SaveDataGameStats;



}

void UHuntSaveGame::SaveLoadData_2(FArchive& Ar, float SaveCurrentPlayerHealth, float SaveMaxPlayerHealth, float SaveCurrentPlayerAragon, float SaveMaxPlayerAragon)
{
	Ar << SaveCurrentPlayerHealth;
	Ar << SaveCurrentPlayerAragon;
	Ar << SaveMaxPlayerAragon;
	Ar << SaveMaxPlayerHealth;
}

bool UHuntSaveGame::SaveGameDataToFile(const FString& FullFilePath)
{

	FBufferArchive ToBinary;
	bool bSucceeded = false;
	//note that the supplied FString must be the entire Filepath
   //  if writing it out yourself in C++ make sure to use the \\
    //  for example:

	//FString SavePath = FPaths::GameAgnosticSavedDir();

	//Call Save and Load function
	SaveLoadData(ToBinary, SavedPlayerStats, SavedPlayerInventory, SavedPlayerGameData);
	//SaveLoadData_2(ToBinary, SavedPlayerStats.SavedCurrentPlayerHealth, SavedPlayerStats.SavedMaxPlayerHealth, SavedPlayerStats.SavedCurrentPlayerAragon, SavedPlayerStats.SavedMaxPlayerAragon);

	if (FFileHelper::SaveArrayToFile(ToBinary, *FullFilePath))
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, TEXT("Save Success!"));
		return true;
	}

	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("File Could Not Be Saved!"));
	return false;
}

bool UHuntSaveGame::LoadGameDataToFile(const FString& FullFilePath, FHuntPlayerStatsData& SaveDataPlayerStats, FHuntPlayerWeaponStatsData& SaveDataPlayerInventory, FHuntSavedGameData& SaveDataGameStats)
{
	//Load the data array,

	TArray<uint8> TheBinaryArray;
	if (FPlatformFileManager::Get().GetPlatformFile().FileExists(*FullFilePath)) // if file exists
	{
		if (!FFileHelper::LoadFileToArray(TheBinaryArray, *FullFilePath))
		{
			//ClientMessage("FFILEHELPER:>> Invalid File");
			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, TEXT("FFILEHELPER:>> Invalid File, Loading Failed, deleting the file now!"));
			FPlatformFileManager::Get().GetPlatformFile().DeleteFile(*FullFilePath);
			return false;

		}
		else
		{
			FMemoryReader FromBinary = FMemoryReader(TheBinaryArray, true); //true, free data after done
			FromBinary.Seek(0);  // dunno what this does exactly
			SaveLoadData_2(FromBinary, SavedPlayerStats.SavedCurrentPlayerHealth, SavedPlayerStats.SavedMaxPlayerHealth, SavedPlayerStats.SavedCurrentPlayerAragon, SavedPlayerStats.SavedMaxPlayerAragon);

			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("Loaded File Size"));
			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, FString::FromInt(TheBinaryArray.Num()));
			return true;
		}

	}
	else //file doesn't exist
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("There is no Save file in this location!"));
		return false;
	}
	return false;
}