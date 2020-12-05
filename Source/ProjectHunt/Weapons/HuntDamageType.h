// Copyright 2020 Brandon Jones. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/DamageType.h"
#include "HuntWeapon.h"
#include "HuntDamageType.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTHUNT_API UHuntDamageType : public UDamageType
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Damage)
		class UForceFeedbackEffect* HitFFE;

	UPROPERTY(Category = Damage, EditDefaultsOnly, BlueprintReadWrite, Meta = (Bitmask, BitmaskEnum = "EWeaponAmmoType"))
		int32 iWeaponAmmoBitmask = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Damage)
		EAmmoType UsedWeaponAmmoType;
	
};
