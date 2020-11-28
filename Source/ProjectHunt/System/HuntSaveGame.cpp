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





