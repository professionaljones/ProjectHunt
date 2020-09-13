// Copyright 2020 Brandon Jones. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Interfaces/Game/HuntDifficultyInterface.h"
#include "ProjectHuntGameMode.generated.h"


//Game mode difficulty, can be used for both Story and Arena mode
UENUM(BlueprintType)
enum EGameDifficulty
{
	GD_None UMETA(DisplayName = "No Difficulty"),
	GD_Easy UMETA(DisplayName = "Easy Mode"),
	GD_Normal UMETA(DisplayName = "Normal Mode"),
	GD_Hard UMETA(DisplayName = "Hard Mode"),
	GD_VeryHard UMETA(DisplayName = "Extreme Mode"),
	GD_TMD UMETA(DisplayName = "Trish Must Die Mode")

};

UCLASS(minimalapi)
class AProjectHuntGameMode : public AGameModeBase, public IHuntDifficultyInterface
{
	GENERATED_BODY()

public:
	AProjectHuntGameMode();

	//What is the player's current rank 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Difficulty")
		float PlayerCurrentRankAmount = 0.0f;

	//What is the player's current rank percentage
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Difficulty")
		float PlayerCurrentRankPercentage = 0.0f;

	//What is the min rank for the current difficulty
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Difficulty")
		float CurrentRankMinReference = 0.0f;

	//What is the max rank for the current difficulty
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Difficulty")
		float CurrentRankMaxReference = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Difficulty")
		float MaxPlayerRank = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Difficulty")
		float NormalRankMin = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Difficulty")
		float NormalRankMax = 1.50f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Difficulty")
		float HardRankMin = 1.50f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Difficulty")
		float HardRankMax = 2.25f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Difficulty")
		float VeryHardRankMin = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Difficulty")
		float VeryHardRankMax = 2.75f;

	UFUNCTION(BlueprintCallable, Category = "Difficulty")
		void ModifyRank(float RankModAmount);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Difficulty")
		bool bShouldUseDynamicDifficulty = false;

	
	UFUNCTION(BlueprintCallable, Category = "Diffculty")
	void SetGameDifficulty(TEnumAsByte<EGameDifficulty> NewDifficulty);
		

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Difficulty|Reference")
		float NormalMinRankReferenceAmount = 2800.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Difficulty|Reference")
		float NormalMaxRankReferenceAmount = 3300.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Difficulty|Reference")
		float HardMaxRankReferenceAmount = 5200.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Difficulty|Reference")
		float VeryHardRankReferenceAmount = 6400.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Difficulty|Reference")
		float ExtremeRankReferenceAmount = 8200.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Difficulty")
	TEnumAsByte<EGameDifficulty> CurrentGameDifficulty;



	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Difficulty")
		int GameDifficulty = 2;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Difficulty")
		int GetGameDifficulty();

	UFUNCTION(BlueprintCallable, Category = "Difficulty")
		void SetStartingDifficulty();

	UFUNCTION(BlueprintCallable, Category = "Difficulty")
		void MeasureRank();

	
};



