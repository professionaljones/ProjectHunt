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

	/*UPROPERTY(VisibleAnywhere, Category = "Player|Stats")
		FPlayerSaveableStats SavedPlayerUnlockedAbilities;*/

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

	

private:
	
public:

	

};
