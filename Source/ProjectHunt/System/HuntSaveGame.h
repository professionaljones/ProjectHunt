// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "ProjectHunt/Character/HuntStatsComponent.h"
#include "ProjectHunt/Weapons/HuntWeapon.h"
#include "ProjectHunt/Character/Player/HuntPlayerCharacter.h"
#include "Serialization/ObjectAndNameAsStringProxyArchive.h"
#include "HuntSaveGame.generated.h"

struct FHuntSaveGameArchive : public FObjectAndNameAsStringProxyArchive
{
	FHuntSaveGameArchive(FArchive& InInnerArchive) : FObjectAndNameAsStringProxyArchive(InInnerArchive, true)
	{
		ArIsSaveGame = true;
		ArNoDelta = false;
	}
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

	UPROPERTY(VisibleAnywhere, Category = "Player|Inventory")
		TMap<int, class AHuntWeapon*> SavedPlayerInventory;

	UPROPERTY(VisibleAnywhere, Category = "Player|Inventory")
		FWeaponStatsData SavedPistolStats;

	UPROPERTY(VisibleAnywhere, Category = "Player|Inventory")
		FWeaponStatsData SavedRifleStats;

	UPROPERTY(VisibleAnywhere, Category = "Player|Inventory")
		FWeaponStatsData SavedShotgunStats;

	UPROPERTY(VisibleAnywhere, Category = "Player|Stats")
		float SavedPlayerItemPercentage;

	UPROPERTY(VisibleAnywhere, Category = "Player|Stats")
		float SavedPlayerCurrentDP;

	UPROPERTY(VisibleAnywhere, Category = "Player|Stats")
		TEnumAsByte<EPlayerSuit> SavedCurrentSuit;

	UPROPERTY(VisibleAnywhere, Category = "Player|Stats")
		TEnumAsByte<ESuitPowerModifiers> SavedPowerModifierOne;

	UPROPERTY(VisibleAnywhere, Category = "Player|Stats")
		TEnumAsByte<ESuitPowerModifiers> SavedPowerModifierTwo;

	UPROPERTY(VisibleAnywhere, Category = "Game")
		FString SaveCurrentLevelName;

	UPROPERTY(VisibleAnywhere, Category = "Game")
		FTimespan SavedCurrentPlayTime;


	UPROPERTY(VisibleAnywhere, Category = "Game")
		FString CurrentManualSaveSlotName;


	float GetPlayerCurrentHealth();

	float GetPlayerMaxHealth();



};
