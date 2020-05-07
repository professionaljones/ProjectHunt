// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectHunt/ProjectHuntCharacter.h"
#include "HuntPlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTHUNT_API AHuntPlayerCharacter : public AProjectHuntCharacter
{
	GENERATED_BODY()
	
public:
	AHuntPlayerCharacter();

public:
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,SaveGame, Category = "Player|Inventory")
		TMap<int, class AHuntWeapon*> WeaponInventory;

};
