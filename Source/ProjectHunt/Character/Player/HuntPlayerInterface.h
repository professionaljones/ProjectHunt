// Copyright 2020 Brandon Jones. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ProjectHunt/Weapons/HuntWeapon.h"
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

	//Called by player and UI to show/hide the Pause Menu
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|Player")
		void TogglePauseMenu();

	//Called by UI to retarget user input to the game
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|Player")
		void OnReturnToGame();

	//Called by Doors when the player uses the wrong item type to attempt to open it
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|Player")
		void OnDoorOpenRefuse();

	//Called by Player Character when the player dies
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|Player")
		void OnPlayerDeath();

	//Called by system when player uses Data Points to purchase an item/upgrade
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|Player")
		void OnStorePurchase(int32 StorePrice);

	//Called by system to enable/disable Movement input
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|Player")
		void ToggleMovementInput(bool bToggleInput);

	//Called by system to enable/disable Camera input
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|Player")
		void ToggleLookInput(bool bToggleInput);

	//Called by system to enable/disable ALL input
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|Player")
		void ToggleGeneralInput(bool bToggleInput);

	//Called by system to increase player's style gauge
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|Player")
		void OnModifyStyle(float NewStyleAmount);

	//Called by system to increase player's score in Arena Mode
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|Player")
		void OnModifyArenaScore(float NewStyleAmount);

	//Called by system when player picks up a new weapon
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|Player")
		void OnPlayerWeaponPickup(TSubclassOf<AHuntWeapon> NewWeapon);

	//Called by system when player picks up an upgrade - add to collection percentage
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|Player")
		void OnPlayerPickupItem(float fItemCollectPercentage);

	//Called by system when player unlocks the ability to use Aragon
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|Player")
		void OnPlayerUnlockAragon(bool bIsUnlocked);

	//Called by system when player unlocks the ability to use the Missile Launcher
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|Player")
		void OnPlayerUnlockMissiles(bool bIsUnlocked);

	//Called by system when player unlocks the ability to wall run
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|Player")
		void OnPlayerUnlockWallrun(bool bIsUnlocked);

	//Called by system when player unlocks the ability to dash
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|Player")
		void OnPlayerUnlockDash(bool bIsUnlocked);

	//Get the player's aiming status
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|Player")
		bool GetPlayerAimStatus();

};
