// Copyright 2020 Brandon Jones. All Rights Reserved.

#pragma once

#include "ProjectHunt/ProjectHuntCharacter.h"
#include "HuntPlayerInterface.h"
#include "PlayerStatsComponent.h"
#include "HuntPlayerCharacter.generated.h"

//What is the player's current suit level
UENUM(BlueprintType)
enum EPlayerSuit
{
	Suit_Standard,
	Suit_Version2,
	Suit_Version3,
	Suit_Version4

};

USTRUCT(BlueprintType)
struct FPlayerSaveableStats : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

		//Has the player unlocked the ability to dash
		UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame, Category = "Player|Movement")
		bool bUnlockedDash = false;

	//Has the player unlocked the ability to wallrun
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame, Category = "Player|Movement")
		bool bUnlockedWallrun = false;
};
/**
 *
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FUpdatePlayerHUD);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSecondaryPlayerUpdate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUpdateWeaponSlot, TEnumAsByte<EWeaponType>, NewWeaponType);
UCLASS()
class PROJECTHUNT_API AHuntPlayerCharacter : public AProjectHuntCharacter, public IHuntPlayerInterface

{
	GENERATED_BODY()

public:
	AHuntPlayerCharacter();

public:

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Player|Data")
		FUpdatePlayerHUD UpdatePlayerHUD_Delegate;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Player|Data")
		FSecondaryPlayerUpdate SecondaryPlayerUpdateDelegate;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Player|Data")
		FUpdateWeaponSlot UpdateWeaponSlotEvent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame, Category = "Player|Movement")
		bool bCanDash = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame, Category = "Player|Movement")
		bool bCanWallrun = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame, Category = "Player|Movement")
		bool bHasMissileLauncher = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, SaveGame, Category = "Player|Inventory")
		TMap<int32, class AHuntWeapon*> WeaponInventory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame, Category = "Player|Weapons")
		int32 CurrentMissileCount = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame, Category = "Player|Weapons")
		int32 MaxMissileCount = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame, Category = "Player|Weapons")
		bool bAreMissilesEmpty = false;

	//This is what the UI will report the owner's Current Missiles is
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player|Weapons")
		float UI_CurrentMissileCount = 0.0f;

	//This is what the UI will report the owner's Max Missiles is
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player|Weapons")
		float UI_MaxMissileCount = 0.0f;

	//This is the player's maximum health amount
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player|Weapons")
		float MaxHealthLimit = 1500.0f;

	//This is the player's maximum missile count
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player|Weapons")
		int MaxMissileLimit = 255;


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, SaveGame, Category = "Player|Suit")
		TEnumAsByte<EPlayerSuit> CurrentPlayerSuit;

	//How fast can the player move on land
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame, Category = "Movement|Walking")
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

	//How many jumps can the character execute
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame, Category = "Movement|Jumping")
		int32 JumpCount = 2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame, Category = "Movement|Jumping")
		float PlayerAirControl = 0.16f;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Player Data|Movement")
		int32 GetJumpCount();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Player Data|Movement")
		int32 GetDashCount();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Player Data|Weapons")
		bool CanPlayerUseMissiles();

protected:
	virtual void BeginPlay() override;

public:

	//This will toggle the @param bool
	UFUNCTION(BlueprintCallable, Category = "Player|Data")
		void UnlockAbility(bool bUnlockAbility);

	//This returns the owner's current Missiles
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Player|Data")
		int32 GetCurrentMissiles();

	//This returns the owner's max Missiles
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Player|Data")
		int32 GetMaxMissiles();

	//This will tell another function to remove current Missiles
	UFUNCTION(BlueprintCallable, Category = "Player|Data")
		void ConsumeMissiles(int32 ConsumeMissileAmount);

	//This will add missiles back to the current Missiles
	UFUNCTION(BlueprintCallable, Category = "Player|Data")
		void RecoverMissiles(int32 RecoverAmount);

	//This will modify Max Missiles, then reset current Missiles
	UFUNCTION(BlueprintCallable, Category = "Player|Data")
		void UpgradeMissileCapacity(int32 IncreaseAmount);

	//This will modify Max Missiles, then reset current Missiles
	UFUNCTION(BlueprintCallable, Category = "Player|Stats")
		void SetPlayerSuit(TEnumAsByte<EPlayerSuit> NewPlayerSuit);


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Player", meta = (AllowPrivateAccess = "true"))
		class AHuntPlayerController* MyPlayerController;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Audio, meta = (AllowPrivateAccess = "true"))
		class UAudioComponent* SuitAudioComponent;

	/**
 * Apply damage to this actor.
 * @see https://www.unrealengine.com/blog/damage-in-ue4
 * @param DamageAmount		How much damage to apply
 * @param DamageEvent		Data package that fully describes the damage received.
 * @param EventInstigator	The Controller responsible for the damage.
 * @param DamageCauser		The Actor that directly caused the damage (e.g. the projectile that exploded, the rock that landed on you)
 * @return					The amount of damage actually applied.
 */
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

};
