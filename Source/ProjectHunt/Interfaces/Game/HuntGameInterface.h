// Copyright 2020 Brandon Jones. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "HuntGameInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UHuntGameInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROJECTHUNT_API IHuntGameInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|Player")
		void OnPlayerArenaKill(int ScoreModAmount);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|Arena")
		void OnArenaWaveStart();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|Arena")
		void OnArenaWaveComplete();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|Game")
		void OnTimerElapsed();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|Game")
		void OnRestartFromCheckpoint();
};
