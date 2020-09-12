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
	Mod_EnemyDoubleDamage UMETA(DisplayName = "Twice as Deadly"),
	Mod_RocketsOnly,
	Mod_PlayerSloMo UMETA(DisplayName = "Player Quicksilver"),
	Mod_EnemySloMo UMETA(DisplayName = "Enemy Quicksilver"),
	Mod_Sandbag UMETA(DisplayName = "Sandbag Mode"),
	Mod_Countdown UMETA(DisplayName = "Countdown"),
	Mod_TrishMustDie UMETA(DisplayName = "Trish Must Die"),
	Mod_Fury UMETA(DisplayName = "Fury"),
	Mod_BloodyRain UMETA(DisplayName = "Blood Rain"),
	Mod_MustStyle UMETA(DisplayName = "Must Style")

};


/**
 *
 */
UCLASS()
class PROJECTHUNT_API AProjectHuntGameStateBase : public AGameStateBase, public IHuntGameInterface
{
	GENERATED_BODY()

public:

	//How much time will the timer for the countdown start with
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Countdown")
		float StartingCountdownTimeLimit = 0.0f;

	//How much time does the timer currently have left
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Countdown")
		float CurrentCountdownTime = 0.0f;

	//What was the player's last score in the Arena
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Arena")
		float LastArenaScore = 0;

	//How much should the player's Arena Score be multiplied by
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Arena")
		float ArenaScoreModifier = 1.0f;

	//Current wave count for Arena
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Arena")
		int CurrentWave = 0;

	//How many waves did the player survive last 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Arena")
		int LastArenaWave = 0;


	UFUNCTION(BlueprintCallable, Category = "Arena")
		float GetLastArenaScore();

	//How much time has the player spent in game
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



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Difficulty")
		TArray<TEnumAsByte<EGameModifiers>> ModifiersList;



};
