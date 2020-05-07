// Fill out your copyright notice in the Description page of Project Settings.


#include "HuntSaveGame.h"

UHuntSaveGame::UHuntSaveGame()
{
	SaveSlotName = TEXT("TestSaveSlot");
	UserIndex = 0;
}



void UHuntSaveGame::SetPlayerData(FCharacterStats PlayerStats, TMap<int, class AHuntWeapon*> PlayerInventory)
{
	SavedPlayerStats = PlayerStats;
	SavedPlayerInventory = PlayerInventory;
}

float UHuntSaveGame::GetPlayerCurrentHealth()
{
	return SavedCurrentPlayerAragon;
}

float UHuntSaveGame::GetPlayerMaxHealth()
{
	return SavedMaxPlayerHealth;
}
