// Fill out your copyright notice in the Description page of Project Settings.


#include "HuntSaveGame.h"

UHuntSaveGame::UHuntSaveGame()
{
	SaveSlotName = TEXT("TestSaveSlot");
	UserIndex = 0;
}




float UHuntSaveGame::GetPlayerCurrentHealth()
{
	return SavedCurrentPlayerAragon;
}

float UHuntSaveGame::GetPlayerMaxHealth()
{
	return SavedMaxPlayerHealth;
}
