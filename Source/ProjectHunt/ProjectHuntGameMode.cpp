// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "ProjectHuntGameMode.h"
#include "ProjectHuntHUD.h"
#include "ProjectHuntCharacter.h"
#include "UObject/ConstructorHelpers.h"

AProjectHuntGameMode::AProjectHuntGameMode()
	: Super()
{
	//// set default pawn class to our Blueprinted character
	//static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Dynamic/Blueprints/Player/BP_FP_TrishPlayerCharacter"));
	//DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AProjectHuntHUD::StaticClass();

	//SetStartingDifficulty();
}

int AProjectHuntGameMode::GetGameDifficulty()
{
	return GameDifficulty;
}


void AProjectHuntGameMode::SetStartingDifficulty()
{
	switch (GameDifficulty)
	{
	case 2:

		CurrentRankReference = NormalRankReference;
		PlayerRank = NormalRankMin;
		break;
	case 3:
		CurrentRankReference = HardRankReference;
		PlayerRank = HardRankMin;
		break;
	case 4:
		CurrentRankReference = VeryHardRankReference;
		PlayerRank = VeryHardRankMin;
		break;
	case 5:
		CurrentRankReference = ExtremeRankReference;
		break;
	default:
		CurrentRankReference = NormalRankReference;
		PlayerRank = NormalRankMin;
		break;
	}
}

void AProjectHuntGameMode::MeasureRank()
{

	switch (GameDifficulty)
	{
	case 2:
		if (CurrentRankReference >= 4000)
		{
			PlayerRank++;
		}
		if (CurrentRankReference >= 5000)
		{
			PlayerRank++;
		}
		if (CurrentRankReference <= NormalRankReference)
		{
			CurrentRankReference = NormalRankReference;
			PlayerRank = NormalRankMin;
		}
		if (CurrentRankReference >= HardRankReference)
		{
			CurrentRankReference = HardRankReference;
			PlayerRank = NormalRankMax;
		}
		if (PlayerRank >= NormalRankMax)
		{
			PlayerRank = NormalRankMax;
		}
	}
}
