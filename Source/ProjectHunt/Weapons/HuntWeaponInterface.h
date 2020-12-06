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

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|Weapon")
		void OnWeaponEquip();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|Weapon")
		void OnWeaponSwitch();

	UFUNCTION(BlueprintCallable,BlueprintImplementableEvent,Category = "Event Response|Weapon")
		void OnWeaponFire();

	//This is used on a per weapon basis to spawn a unique projectile
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|Weapon")
		void OnWeaponFireUnique();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|Weapon")
		void OnWeaponAltFire();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|Weapon")
		void OnWeaponEndAltFire();
};
