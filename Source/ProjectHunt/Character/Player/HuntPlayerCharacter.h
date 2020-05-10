// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectHunt/ProjectHuntCharacter.h"
#include "HuntPlayerCharacter.generated.h"

//What is the player's current style rank
UENUM(BlueprintType)
enum EPlayerSuit
{
	Suit_Standard,
	Suit_Version2,
	Suit_Version3,
	Suit_Version4

};
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
		TMap<TEnumAsByte<EWeaponType>, class AHuntWeapon*> WeaponInventory;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,SaveGame,Category = "Player|Suit")
		TEnumAsByte<EPlayerSuit> PlayerSuit;



};
