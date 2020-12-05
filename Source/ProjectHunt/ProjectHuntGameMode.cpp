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

void AProjectHuntGameMode::ModifyRank(float RankModAmount)
{
	float Mod = RankModAmount * 1.0f;
	PlayerCurrentRankAmount += Mod;
	MeasureRank();
}

void AProjectHuntGameMode::SetGameDifficulty(TEnumAsByte<EGameDifficulty> NewDifficulty)
{
	CurrentGameDifficulty = NewDifficulty;
	switch (CurrentGameDifficulty)
	{
	case EGameDifficulty::GD_Easy:
	{
		/*GameDifficulty = 1;
		SetStartingDifficulty();*/
		break;
	}
	case EGameDifficulty::GD_Normal:
	{
		GameDifficulty = 2;
		SetStartingDifficulty();
		break;
	}
	case EGameDifficulty::GD_Hard:
	{
		GameDifficulty = 3;
		SetStartingDifficulty();
		break;
	}
	case EGameDifficulty::GD_VeryHard:
	{
		GameDifficulty = 4;
		SetStartingDifficulty();
		break;
	}
	case EGameDifficulty::GD_TMD:
	{
		GameDifficulty = 5;
		SetStartingDifficulty();
		break;
	}
	case EGameDifficulty::GD_None:
		break;
	}
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
		PlayerCurrentRankAmount = NormalMinRankReferenceAmount;
		PlayerCurrentRankPercentage = NormalRankMin;
		MaxPlayerRank = NormalRankMax;
		break;
	case 3:
		PlayerCurrentRankAmount = NormalMaxRankReferenceAmount;
		PlayerCurrentRankPercentage = HardRankMin;
		MaxPlayerRank = HardRankMax;
		break;
	case 4:
		PlayerCurrentRankAmount = HardMaxRankReferenceAmount;
		PlayerCurrentRankPercentage = VeryHardRankMin;
		MaxPlayerRank = VeryHardRankMin;
		break;
	case 5:
		PlayerCurrentRankAmount = VeryHardRankReferenceAmount;
		PlayerCurrentRankPercentage = VeryHardRankMax;
		break;
	default:
		PlayerCurrentRankAmount = NormalMinRankReferenceAmount;
		PlayerCurrentRankPercentage = NormalRankMin;
		break;
	}
}

void AProjectHuntGameMode::MeasureRank()
{
	if (bShouldUseDynamicDifficulty)
	{
		switch (GameDifficulty)
		{
		case 2:
			//PlayerCurrentRankAmount = NormalMinRankReferenceAmount;
			if (PlayerCurrentRankAmount <= NormalMinRankReferenceAmount)
			{
				PlayerCurrentRankAmount = NormalMinRankReferenceAmount;
				PlayerCurrentRankPercentage = NormalRankMin;
			}
			if (PlayerCurrentRankAmount >= NormalMaxRankReferenceAmount)
			{
				PlayerCurrentRankAmount = NormalMaxRankReferenceAmount;
				PlayerCurrentRankPercentage = NormalRankMax;
			}
			break;
		case 3:
		{
			if (PlayerCurrentRankAmount <= NormalMaxRankReferenceAmount)
			{
				PlayerCurrentRankAmount = NormalMaxRankReferenceAmount;
				PlayerCurrentRankPercentage = HardRankMin;
			}
			if (PlayerCurrentRankAmount >= HardMaxRankReferenceAmount)
			{
				PlayerCurrentRankAmount = HardMaxRankReferenceAmount;
				PlayerCurrentRankPercentage = HardRankMax;
			}
			if (PlayerCurrentRankPercentage >= HardRankMax)
			{
				PlayerCurrentRankPercentage = HardRankMax;
			}
			break;
		}
		case 4:
		{
			if (PlayerCurrentRankAmount <= HardMaxRankReferenceAmount)
			{
				PlayerCurrentRankAmount = HardMaxRankReferenceAmount;
				PlayerCurrentRankPercentage = VeryHardRankMin;
			}
			if (PlayerCurrentRankAmount >= VeryHardRankReferenceAmount)
			{
				PlayerCurrentRankAmount = VeryHardRankReferenceAmount;
				PlayerCurrentRankPercentage = VeryHardRankMax;
			}
			if (PlayerCurrentRankPercentage >= VeryHardRankMax)
			{
				PlayerCurrentRankPercentage = VeryHardRankMax;
			}
			break;
		}
		case 5:
		{
			if (PlayerCurrentRankAmount <= VeryHardRankReferenceAmount)
			{
				PlayerCurrentRankAmount = VeryHardRankReferenceAmount;
				PlayerCurrentRankPercentage = VeryHardRankMax;
			}
			if (PlayerCurrentRankAmount >= ExtremeRankReferenceAmount)
			{
				PlayerCurrentRankAmount = ExtremeRankReferenceAmount;
				PlayerCurrentRankPercentage = VeryHardRankMax;
			}
			if (PlayerCurrentRankPercentage >= VeryHardRankMax)
			{
				PlayerCurrentRankPercentage = VeryHardRankMax;
			}
			break;
		}
		case 0:
		{
			if (PlayerCurrentRankAmount <= NormalMinRankReferenceAmount)
			{
				PlayerCurrentRankAmount = NormalMinRankReferenceAmount;
				PlayerCurrentRankPercentage = NormalRankMin;
			}
			if (PlayerCurrentRankAmount >= NormalMaxRankReferenceAmount)
			{
				PlayerCurrentRankAmount = NormalMaxRankReferenceAmount;
				PlayerCurrentRankPercentage = NormalRankMax;
			}
			if (PlayerCurrentRankPercentage >= NormalRankMax)
			{
				PlayerCurrentRankPercentage = NormalRankMax;
			}
			break;
		}
		}
	}

}
