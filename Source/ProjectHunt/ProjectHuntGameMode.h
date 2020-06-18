// Copyright 2020 Brandon Jones. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Interfaces/Game/HuntDifficultyInterface.h"
#include "ProjectHuntGameMode.generated.h"

UCLASS(minimalapi)
class AProjectHuntGameMode : public AGameModeBase, public IHuntDifficultyInterface
{
	GENERATED_BODY()

public:
	AProjectHuntGameMode();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Difficulty")
		float PlayerRank = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Difficulty")
		float CurrentRankReference = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Difficulty")
		float MaxPlayerRank = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Difficulty")
		float NormalRankMin = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Difficulty")
		float NormalRankMax = 7.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Difficulty")
		float HardRankMin = 6.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Difficulty")
		float HardRankMax = 12.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Difficulty")
		float VeryHardRankMin = 12.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Difficulty")
		float VeryHardRankMax = 18.0f;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Difficulty|Reference")
		float NormalRankReference = 3300.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Difficulty|Reference")
		float HardRankReference = 5200.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Difficulty|Reference")
		float VeryHardRankReference = 6400.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Difficulty|Reference")
		float ExtremeRankReference = 8200.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Difficulty")
		int GameDifficulty = 2;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Difficulty")
		int GetGameDifficulty();

	UFUNCTION(BlueprintCallable, Category = "Difficulty")
		void SetStartingDifficulty();

	UFUNCTION(BlueprintCallable, Category = "Difficulty")
		void MeasureRank();
};



