// Copyright 2020 Brandon Jones. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "HuntCharacterInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UHuntCharacterInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROJECTHUNT_API IHuntCharacterInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	//Use to call BP Event Dispatcher for updating UI
	UFUNCTION(BlueprintCallable,BlueprintImplementableEvent, Category = "Event Response|Character")
	void UpdateStatsUI();

	UFUNCTION(BlueprintCallable,BlueprintImplementableEvent, Category = "Event Response|Player")
	void UpdateStyleGauge(float StyleModAmount);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|Player")
		void OnUpgradeHealth(float IncreaseAmount);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|Character")
		void OnTargetScanned(bool bWasPreviouslyScanned);

	
};
