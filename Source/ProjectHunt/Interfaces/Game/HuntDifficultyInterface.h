// Copyright 2020 Brandon Jones. All Rights Reserved.

#pragma once

#include "UObject/Interface.h"
#include "HuntDifficultyInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UHuntDifficultyInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROJECTHUNT_API IHuntDifficultyInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|Game")
		void PlayerDealtDamage(float RankModiferAmount);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|Game")
		void PlayerReceivedDamage(float RankModiferAmount);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|Game")
		float GetPlayerRank();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|Game")
		float GetPlayerRankPercentage();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|Game")
		float GetDifficultyRankMin();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|Game")
		float GetDifficultyRankMax();
};
