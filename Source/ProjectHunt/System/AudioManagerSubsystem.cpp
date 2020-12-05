// Copyright 2020 Brandon Jones. All Rights Reserved.


#include "AudioManagerSubsystem.h"
#include "ProjectHunt/Game/HuntAudioManager.h"
#include "Engine/World.h"

//void UAudioManagerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
//{
//
//}
//
//void UAudioManagerSubsystem::Deinitialize()
//{
//
//}

void UAudioManagerSubsystem::SetNewAudioManager(AHuntAudioManager* NewAudioManager)
{
	if (!CurrentAudioManager)
	{
		FVector Location(0.0f, 0.0f, 0.0f);
		FRotator Rotation(0.0f, 0.0f, 0.0f);
		FActorSpawnParameters SpawnInfo;
		NewAudioManager = GetWorld()->SpawnActor<AHuntAudioManager>(Location, Rotation, SpawnInfo);
		
	}
	if (NewAudioManager)
	{
		CurrentAudioManager = NewAudioManager;
	}
	
}

AHuntAudioManager* UAudioManagerSubsystem::GetAudioManager()
{
	return CurrentAudioManager;
}
