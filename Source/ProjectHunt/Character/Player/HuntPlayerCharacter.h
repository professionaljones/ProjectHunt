// Copyright 2020 Brandon Jones. All Rights Reserved.

#pragma once

#include "ProjectHunt/ProjectHuntCharacter.h"
#include "HuntPlayerInterface.h"
#include "ProjectHunt/Weapons/HuntWeapon.h"
#include "PlayerStatsComponent.h"
#include "HuntPlayerCharacter.generated.h"

//What is the player's current suit level
UENUM(BlueprintType)
enum EPlayerSuit
{
	Suit_Standard UMETA(DisplayName = "Alpha Suit"),
	Suit_Version2 UMETA(DisplayName = "Beta Suit"),
	Suit_Version3 UMETA(DisplayName = "Gamma Suit"),
	Suit_Version4 UMETA(DisplayName = "Aragon Suit")

};

USTRUCT(BlueprintType)
struct FPlayerSaveableStats : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	//Has the player unlocked the ability to dash?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame, Category = "Player|Movement")
		bool bUnlockedDash = false;

	//Has the player unlocked the ability to wall run?

	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame, Category = "Player|Movement")
		bool bUnlockedWallrun = false;

	//Has the player unlocked the ability to use the missile launcher?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame, Category = "Player|Weapons")
		bool bHasMissileLauncher = false;

	//Has the player unlocked the ability to use Aragon abilities?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame, Category = "Player|Aragon")
		bool bUnlockedAragon = false;
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

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Mesh)
		class USkeletalMeshComponent* Mesh1P;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FirstPersonCameraComponent;
	/** Returns Mesh1P subobject **/
	FORCEINLINE class USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

public:

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Player|Data")
		FUpdatePlayerHUD UpdatePlayerHUD_Delegate;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Player|Data")
		FSecondaryPlayerUpdate SecondaryPlayerUpdateDelegate;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Player|Data")
		FUpdateWeaponSlot UpdateWeaponSlotEvent;

	//This struct will hold the player's unlocked abilities (dash, wallrun, double jump, missiles, etc)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player|Stats")
		FPlayerSaveableStats PlayerSavedStats;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame, Category = "Player|Movement")
		bool bCanDash = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame, Category = "Player|Movement")
		bool bCanWallrun = false;



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



	//What is the max number of limits for dashing
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame, Category = "Movement|Dashing")
		int32 MaxDashCount = 2;

	//How many dashes has the character executed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame, Category = "Movement|Dashing")
		int32 CurrentDashCount = 2;

	//Multiplier of character Velocity for dashing - prototyping
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame, Category = "Movement|Dashing")
		float DashVelocityMod = 100.0f;

	//What is the max number of limits for dashing
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame, Category = "Movement|Jumping")
		int32 MaxJumpCount = 2;

	//How many jumps can the character execute
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame, Category = "Movement|Jumping")
		int32 CurrentJumpCount = 2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame, Category = "Movement|Jumping")
		float PlayerAirControl = 0.16f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame, Category = "Movement|Jumping")
		float JumpBlastLimit = 2.50f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame, Category = "Movement|Jumping")
		float JumpBlastChargeModifer = 0.01f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame, Category = "Movement|Jumping")
		float CurrentJumpBlastChargeAmount = 2.50f;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Player Data|Movement")
		int32 GetJumpCount();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Player Data|Movement")
		int32 GetDashCount();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Player Data|Weapons")
		bool CanPlayerUseMissiles();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Player Data|Aragon")
		bool CanPlayerUseAragon();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Player Data|Movement")
		bool CanPlayerDash();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Player Data|Movement")
		bool CanPlayerWallrun();



protected:
	virtual void BeginPlay() override;

public:

	//This will take a bool @param AbilityToToggle, and set it to @param bUnlockAbility
	UFUNCTION(BlueprintCallable, Category = "Player|Data")
		void UnlockAbility(bool AbilityToToggle, bool bUnlockAbility);

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
	UFUNCTION(BlueprintCallable, Category = "Player|Stats")
		void RecoverMissiles(int32 RecoverAmount);

	//This will modify Max Missiles by @param IncreaseAmount , then reset current Missiles

	UFUNCTION(BlueprintCallable, Category = "Player|Stats")
		void UpgradeMissileCapacity(int32 IncreaseAmount);

	//This will modify Max Missiles to @param NewMissileAmount, then reset current Missiles
	UFUNCTION(BlueprintCallable, Category = "Player|Stats")
		void UpdateMissileCapacity(int32 NewMissileAmount);

	//This will update the player's stats according to the new suit

	UFUNCTION(BlueprintCallable, Category = "Player|Stats")
		void SetPlayerSuit(TEnumAsByte<EPlayerSuit> NewPlayerSuit);

	//This will set the player's Current Suit Power

	UFUNCTION(BlueprintCallable, Category = "Player|Stats")
		void SetCurrentSuitPower(TEnumAsByte<ESuitMainAbilities> NewSuitPower);

	//This will set the player's first Power Modifier

	UFUNCTION(BlueprintCallable, Category = "Player|Stats")
		void SetPowerModifierOne(TEnumAsByte<ESuitPowerModifiers> NewPowerModifier);

	//This will set the player's second Power Modifier

	UFUNCTION(BlueprintCallable, Category = "Player|Stats")
		void SetPowerModifierTwo(TEnumAsByte<ESuitPowerModifiers> NewPowerModifier);

	//This will modify Max Dash Count, then reset current Dash Count

	UFUNCTION(BlueprintCallable, Category = "Player|Data")
		void UpdateDashCount(int32 IncreaseAmount);

	//This will modify Max Jump Count, then reset current Jump Count

	UFUNCTION(BlueprintCallable, Category = "Player|Data")
		void UpdateJumpCount(int32 IncreaseAmount);

	UFUNCTION(BlueprintCallable, Category = "Player|Initialization")
		void SetPlayerStats(float NewMaxHealth, float NewMaxAragon, TEnumAsByte<EPlayerSuit> NewPlayerSuit, TEnumAsByte<ESuitMainAbilities> NewSuitPower, TEnumAsByte<ESuitPowerModifiers> NewPowerModifierOne, TEnumAsByte<ESuitPowerModifiers> NewPowerModifierTwo, int32 NewMaxMissileCount, FPlayerSaveableStats NewPlayerSaveableStats, TMap<int32, AHuntWeapon*> NewWeaponInventory, int32 NewCurrentDataPoints);


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Player", meta = (AllowPrivateAccess = "true"))
		class AHuntPlayerController* MyPlayerController;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Audio, meta = (AllowPrivateAccess = "true"))
		class UAudioComponent* SuitAudioComponent;


};
