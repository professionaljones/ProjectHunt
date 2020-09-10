// Copyright 2020 Brandon Jones. All Rights Reserved.

#pragma once

#include "UObject/Interface.h"
#include "HuntWeaponInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI,Blueprintable)
class UHuntWeaponInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROJECTHUNT_API IHuntWeaponInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	/*UFUNCTION(BlueprintCallable,BlueprintImplementableEvent,Category = "Event Response|Weapon")
	void OnWeaponActivate(EAmmoType AmmoTypeUsed);*/

	UFUNCTION(BlueprintCallable,BlueprintImplementableEvent,Category = "Event Response|Weapon")
		void OnWeaponFire();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|Weapon")
		void OnWeaponAltFire();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|Weapon")
		void OnWeaponEndAltFire();
};
