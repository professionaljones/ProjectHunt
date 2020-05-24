// Copyright 2020 Brandon Jones. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "HuntPlayerInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UHuntPlayerInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROJECTHUNT_API IHuntPlayerInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|Player")
		void TogglePauseMenu();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|Player")
		void OnReturnToGame();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|Player")
		void OnPauseGame();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|Player")
		void OnDoorOpenRefuse();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|Player")
		void OnPlayerDeath();
};
