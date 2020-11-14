// Copyright 2020 Brandon Jones. All Rights Reserved.


#include "SaveGameInstanceSubsystem.h"
#define SAVEDATAFILENAME "SampleSavedData"

bool USaveGameInstanceSubsystem::SaveGameData()
{
	if (CurrentSaveSlot.IsEmpty())
	{
		CurrentSaveSlot = FirstSaveSlot;
	}
	const FString& FullFilePath = FPaths::GameAgnosticSavedDir() + CurrentSaveSlot + ".sav";
	//Save the data to binary
	FBufferArchive ToBinary;


	//#if PLATFORM_WINDOWS
	//	FullFilePath = FPaths::ProjectUserDir();
	//#endif 
		//Save binaries to disk

	SaveLoadData(ToBinary, PlayerCharacterReference->PlayerSavedStats, PlayerCharacterReference->PlayerStatsComponent->QuicksilverStats, PlayerCharacterReference->PlayerStatsComponent->ShowstopperStats, PlayerCharacterReference->PlayerStatsComponent->OverloadStats, PlayerCharacterReference->PlayerStatsComponent->DashRushStats, PlayerCharacterReference->PlayerStatsComponent->JumpBlastStats, PlayerCharacterReference->PistolSlot->WeaponStatsData, PlayerCharacterReference->RifleSlot->WeaponStatsData, PlayerCharacterReference->ShotgunSlot->WeaponStatsData, PlayerCharacterReference->PlayerSavedData);

	//No data were saved
	if (ToBinary.Num() <= 0) return false;
	bool result = FFileHelper::SaveArrayToFile(ToBinary, *FullFilePath);
	if (result)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, TEXT("Subsystem Save Success!"));
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, *FullFilePath);
	}

	//Empty the buffer's contents
	ToBinary.FlushCache();
	ToBinary.Empty();
	return result;
}

bool USaveGameInstanceSubsystem::LoadGameData()
{
	const FString& FullFilePath = FPaths::GameAgnosticSavedDir() + CurrentSaveSlot + ".sav";
	TArray<uint8> BinaryArray;

	//load disk data to binary array
	if (!FFileHelper::LoadFileToArray(BinaryArray, *FullFilePath))
	{
		return false;
	}

	if (BinaryArray.Num() <= 0)
	{
		return false;
	}

	//Memory reader is the archive that we're going to use in order to read the loaded data
	FMemoryReader FromBinary = FMemoryReader(BinaryArray, true);
	FromBinary.Seek(0);
	SaveLoadData(FromBinary, PlayerCharacterReference->PlayerSavedStats, PlayerCharacterReference->PlayerStatsComponent->QuicksilverStats, PlayerCharacterReference->PlayerStatsComponent->ShowstopperStats, PlayerCharacterReference->PlayerStatsComponent->OverloadStats, PlayerCharacterReference->PlayerStatsComponent->DashRushStats, PlayerCharacterReference->PlayerStatsComponent->JumpBlastStats, PlayerCharacterReference->PistolSlot->WeaponStatsData, PlayerCharacterReference->RifleSlot->WeaponStatsData, PlayerCharacterReference->ShotgunSlot->WeaponStatsData, PlayerCharacterReference->PlayerSavedData);

	//Empty the buffer's contents
	FromBinary.FlushCache();
	BinaryArray.Empty();
	//Close the stream
	FromBinary.Close();

	return true;
}

void USaveGameInstanceSubsystem::SaveLoadData(FArchive& Ar, FPlayerSaveableStats& PlayerUnlockedStats, FPlayerMainAbilityData& QuicksilverAbilityStats, FPlayerMainAbilityData& ShowstopperAbilityStats, FPlayerMainAbilityData& OverloadAbilityStats, FPlayerPowerModifierData& DashPowerStats, FPlayerPowerModifierData& BlastPowerStats, FWeaponStatsData& SavePistolStats, FWeaponStatsData& SaveRifleStatsData, FWeaponStatsData& SaveShotgunStatsData, FPlayerStatsData& SavePlayerStats)
{
	Ar << PlayerUnlockedStats;
	Ar << QuicksilverAbilityStats;
	Ar << ShowstopperAbilityStats;
	Ar << OverloadAbilityStats;
	Ar << DashPowerStats;
	Ar << BlastPowerStats;
	Ar << SavePistolStats;
	Ar << SaveRifleStatsData;
	Ar << SaveShotgunStatsData;
	Ar << SavePlayerStats;
}
