// Copyright 2020 Brandon Jones. All Rights Reserved.

#pragma once

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
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|Character")
		void UpdateStatsUI();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|Player")
		void UpdateStyleGauge(float StyleModAmount);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|Player")
		void UpdatePlayerDataPoints(int32 DPModAmount);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|Player")
		void OnUpgradeHealth(float IncreaseAmount);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|Character")
		void OnTargetScanned(bool bWasPreviouslyScanned);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|Character")
		void OnAttackTarget();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|Character")
		void OnWeaponFire();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|Character")
		void OnFindCover();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|Player")
		void OnPlayerLockOn(bool bIsLockedOn);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|Character")
		void OnRecoverHealth(float RecoverAmount);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|Character")
		void OnRecoverAragon(float RecoverAmount);

	//Overrideable event for handling death
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|Character")
		void OnCharacterDeath();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|Character")
		void OnInteract();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|Character")
		void OnTakeFireDamage();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|Character")
		void OnTakeIceDamage();


};
