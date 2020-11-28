// Copyright 2020 Brandon Jones. All Rights Reserved.

#pragma once

#include "ProjectHunt/Character/HuntStatsComponent.h"
#include "PlayerStatsComponent.generated.h"

/**
 * 
 */


UCLASS()
class PROJECTHUNT_API UPlayerStatsComponent : public UHuntStatsComponent
{
	GENERATED_BODY()

public:

	//This is the player's current item collect percentage
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player|Stats")
		float fCurrentItemCollectionPercentage = 0.0f;

protected:

	//This is the player's minimum health amount at the start of the game
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player|Stats")
		float StartingHealthLimit = 200.0f;

	//This is the player's maximum health amount
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player|Stats")
		float MaxHealthLimit = 1600.0f;

	//This is the player's maximum health amount
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player|Stats")
		float MaxAragonLimit = 1200.0f;
	
	
};
