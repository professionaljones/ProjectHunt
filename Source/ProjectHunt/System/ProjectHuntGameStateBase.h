// Copyright 2020 Brandon Jones. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "ProjectHunt/Interfaces/Game/HuntGameInterface.h"
#include "ProjectHuntGameStateBase.generated.h"

//Modifiers for Arena Mode, possibly Campaign mode
UENUM(BlueprintType)
enum EGameModifiers
{
	Mod_None,
	Mod_EnemyDoubleDamage,
	Mod_RocketsOnly,
	Mod_PlayerSloMo,
	Mod_EnemySloMo,
	Mod_Sandbag,
	Mod_Countdown

};


/**
 *
 */
UCLASS()
class PROJECTHUNT_API AProjectHuntGameStateBase : public AGameStateBase, public IHuntGameInterface
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Arena")
		float LastArenaScore = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Arena")
		float ArenaScoreModifier = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Arena")
		int CurrentWave = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Arena")
		int LastArenaWave = 0;


	UFUNCTION(BlueprintCallable, Category = "Arena")
		float GetLastArenaScore();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game|Time")
		FTimespan CurrentPlayTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Timers")
		FTimerHandle PlayTimeHandle;

	UFUNCTION(BlueprintCallable, Category = "Game|Time")
		void IncrementPlayTime();

	UFUNCTION(BlueprintCallable, Category = "Arena")
		float UpdatePlayerScore(int ScoreModAmount);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Game|Time")
		FTimespan GetCurrentPlayTime();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game|Time")
		FTimespan PlayTimeModifier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Difficulty")
		TEnumAsByte<EGameModifiers> GameModiferOne;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Difficulty")
		TEnumAsByte<EGameModifiers> GameModiferTwo;





};
