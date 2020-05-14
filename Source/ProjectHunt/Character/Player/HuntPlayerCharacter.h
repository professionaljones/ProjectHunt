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
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FUpdatePlayerHUD);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUpdateWeaponSlot, TEnumAsByte<EWeaponType>, NewWeaponType);
UCLASS()
class PROJECTHUNT_API AHuntPlayerCharacter : public AProjectHuntCharacter

{
	GENERATED_BODY()
	
public:
	AHuntPlayerCharacter();

public:

	UPROPERTY(BlueprintAssignable,BlueprintCallable,Category = "Player|Data")
		FUpdatePlayerHUD UpdatePlayerHUD_Delegate;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Player|Data")
		FUpdateWeaponSlot UpdateWeaponSlotEvent;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,SaveGame, Category = "Player|Inventory")
		TMap<TEnumAsByte<EWeaponType>, class AHuntWeapon*> WeaponInventory;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,SaveGame,Category = "Player|Suit")
		TEnumAsByte<EPlayerSuit> PlayerSuit;

	//How fast can the player move on land
	UPROPERTY(EditAnywhere, BlueprintReadWrite,SaveGame,Category = "Movement|Walking")
		float MovementSpeed = 1300.0f;

	//What is the max number of limits for dashing
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame, Category = "Movement|Dashing")
		int32 MaxDashCount = 2;

	//How many dashes has the character executed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame, Category = "Movement|Dashing")
		int32 DashCount = 2;

	//Multiplier of character Velocity for dashing - prototyping
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame, Category = "Movement|Dashing")
	float DashVelocityMod = 100.0f;

	//What is the max number of limits for dashing
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame, Category = "Movement|Jumping")
		int32 MaxJumpCount = 2;

	//How many dashes has the character executed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame, Category = "Movement|Jumping")
		int32 JumpCount = 2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame, Category = "Movement|Jumping")
		float PlayerAirControl = 0.16f;

	UFUNCTION(BlueprintCallable,BlueprintPure, Category = "Player Data|Movement")
		int32 GetJumpCount();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Player Data|Movement")
		int32 GetDashCount();

protected:

public:
	
};
