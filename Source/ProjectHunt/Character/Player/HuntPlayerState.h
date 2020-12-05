// Copyright 2020 Brandon Jones. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "HuntPlayerInterface.h"
#include "HuntPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTHUNT_API AHuntPlayerState : public APlayerState, public IHuntPlayerInterface
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Arena")
	float CurrentArenaScore = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Arena")
		int CurrentArenaWave = 0;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Arena")
		float GetPlayerArenaScore();
	
};
