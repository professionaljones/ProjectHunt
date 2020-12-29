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

float AProjectHuntGameStateBase::UpdatePlayerScore(int ScoreModAmount)
{
	float NewPlayerScoreMod = 0.0f;
	NewPlayerScoreMod = ScoreModAmount * ArenaScoreModifier;
	return NewPlayerScoreMod;
}

FTimespan AProjectHuntGameStateBase::GetCurrentPlayTime()
{
	return CurrentPlayTime;
}

TArray<AActor*> AProjectHuntGameStateBase::GetCurrentEnemies()
{
	return CurrentEnemies;
}

