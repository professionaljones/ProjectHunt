// Copyright 2020 Brandon Jones. All Rights Reserved.


#include "ProjectHuntGameStateBase.h"



float AProjectHuntGameStateBase::GetLastArenaScore()
{
	return LastArenaScore;
}

void AProjectHuntGameStateBase::IncrementPlayTime()
{
	CurrentPlayTime = CurrentPlayTime + PlayTimeModifier;
}

void AProjectHuntGameStateBase::BeginPlay()
{
	//Start incrementing our play time
	GetWorldTimerManager().SetTimer(PlayTimeHandle, this, &AProjectHuntGameStateBase::IncrementPlayTime, 1.0f, true);
}
