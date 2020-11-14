// Copyright 2020 Brandon Jones. All Rights Reserved.


#include "HuntGameInstanceUGC.h"

UHuntGameInstanceUGC::UHuntGameInstanceUGC()
{
	RecordingName = "MyReplay";
	friendlyRecordingName = "My Replay";
}

void UHuntGameInstanceUGC::Init()
{
	// Instantiate the registry and find mod packages
	UGCRegistry = NewObject<UUGCRegistry>(this);
	UGCRegistry->FindUGCPackages();
	Super::Init();
}

void UHuntGameInstanceUGC::StartRecording()
{
	StartRecordingReplay(RecordingName, friendlyRecordingName);
}

void UHuntGameInstanceUGC::StopRecording()
{
	StopRecordingReplay();
}

void UHuntGameInstanceUGC::StartReplay()
{
	PlayReplay(RecordingName, nullptr);
}

void UHuntGameInstanceUGC::AttemptToSave()
{
	
	if (UHuntSaveGame* SaveGameInstance = Cast<UHuntSaveGame>(UGameplayStatics::CreateSaveGameObject(UHuntSaveGame::StaticClass())))
	{
		
		AHuntPlayerCharacter* PlayerCharacter = Cast<AHuntPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		SaveGameInstance->SavedPlayerStats.SavedPlayerTransform = PlayerCharacter->GetActorTransform();
		SaveGameInstance->SavedPlayerStats.SavedCurrentPlayerHealth = PlayerCharacter->PlayerStatsComponent->GetCurrentHealth();
		SaveGameInstance->SavedPlayerStats.SavedMaxPlayerHealth = PlayerCharacter->PlayerStatsComponent->GetMaxHealth();
		SaveGameInstance->SavedPlayerStats.SavedCurrentPlayerAragon = PlayerCharacter->PlayerStatsComponent->GetCurrentAragon();
		SaveGameInstance->SavedPlayerStats.SavedMaxPlayerAragon = PlayerCharacter->PlayerStatsComponent->GetMaxAragon();
		SaveGameInstance->SavedPlayerStats.SavedPlayerCurrentDP = PlayerCharacter->CurrentDataPoints;
		SaveGameInstance->SavedPlayerStats.SavedCurrentSuit = PlayerCharacter->CurrentPlayerSuit;
		SaveGameInstance->SaveGameDataToFile(FPaths::GameAgnosticSavedDir());
	}
	//if (UGameplayStatics::SaveDataToSlot(InSaveData, SlotNameString, UserIndexInt32))
	//{
	//	// The operation succeeded, and InSaveData has been written to the save file defined by the slot name and user ID we provided.
	//}
}
