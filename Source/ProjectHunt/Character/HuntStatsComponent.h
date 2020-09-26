// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectHunt/ProjectHunt.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "Runtime/Core/Public/Serialization/Archive.h"
#include "HuntStatsComponent.generated.h"


/*These are the main powers that the player will be able to use via Aragon
* They serve to tell us what power they want to use and how that should influence/manipulate the player or the world around them
* Quicksilver - Slows down the world and the player, can be leveled up to only affect the world, ignoring the player
* Showstopper - Reverses eligible Actors to allow for tactial planning in combat or unique puzzle solutions (temp name)
* Overload - Speeds up player, boosts damage output and allows them to regenerate health
*/

UENUM(BlueprintType)
enum ESuitMainAbilities
{
	MA_None UMETA(DisplayName = "Unequipped"),
	MA_Quicksilver UMETA(DisplayName = "Quicksilver"),
	MA_Showstopper UMETA(DisplayName = "Showstopper"),
	MA_Overload UMETA(DisplayName = "Overload")
};

/*These are the modifiers to the player's base abilities (jumping, dashing, etc) that add new effects when using them
* Rush - adds an attack to the player's dash, can be used to destroy obstacles in mid air or attack enemies upon landing
* Blast - Allows the player to jump to a much greater height than normal, can be used for puzzle platforming
*/

UENUM(BlueprintType)
enum ESuitPowerModifiers
{
	PM_None UMETA(DisplayName = "Unequipped"),
	PM_Rush UMETA(DisplayName = "Dash Rush"),
	PM_Blast UMETA(DisplayName = "Jump Blast"),
	
};

/* This struct serves as a way to maintain the info about the player's unlocked main abilities and allows us to add new effects at the appropriate time*/

USTRUCT(BlueprintType)
struct FPlayerMainAbilityData : public FTableRowBase
{

	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ability")
	//The Ability in question
	TEnumAsByte<ESuitMainAbilities> CurrentAbility;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
	//The Ability's current level
	int32 CurrentAbilityLevel = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
	//The Ability's Max level
	int32 MaxAbilityLevel = 3;

	//What is the price of this upgrade?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
		float AbilityUpgradePrice;
};

/* This struct, much like FPlayerMainAbilityData, serves to maintain info about the player's unlocked power modifiers and add new effects */

USTRUCT(BlueprintType)
struct FPlayerPowerModifierData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Power")
	//The Ability in question
	TEnumAsByte<ESuitPowerModifiers> CurrentPowerModifier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power")
	//The PM's current level
	int32 CurrentPowerModifierLevel = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power")
	//The PM's Max level
	int32 MaxPowerModifierLevel = 3;

	//What is the price of this upgrade?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power")
		float PowerUpgradeAbility;
};

/**HuntStatsComponent serves as a container for a character's stats and functions
for adding, reducing and changing the overall values **/
UCLASS(Blueprintable, BlueprintType,ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PROJECTHUNT_API UHuntStatsComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UHuntStatsComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//How much health does the owner currently have
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, SaveGame, Category = "Stats|Health")
		float CurrentHealth = 0.0f;

	//How much health does the owner start with
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, SaveGame, Category = "Stats|Health")
		float MaxHealth = 100.0f;

	//How much Aragon does the owner currently have
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, SaveGame, Category = "Stats|Aragon")
		float CurrentAragon = 0.0f;

	//How much Aragon does the owner start with
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, SaveGame, Category = "Stats|Aragon")
		float MaxAragon = 0.0f;

	//By how many points does the owner's Current Aragon recharge
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, SaveGame, Category = "Stats|Aragon")
		float AragonRechargeAmount = 0.0f;


	//This is what the UI will report the owner's Max Health is
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats|Health")
		float UI_CurrentHealth = 0.0f;

	//This is what the UI will report the owner's Max Health is
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats|Health")
		float UI_MaxHealth = 100.0f;

	//This is what the UI will report the owner's Current Aragon is
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats|Aragon")
		float UI_CurrentAragon = 0.0f;

	//This is what the UI will report the owner's Max Aragon is
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats|Aragon")
		float UI_MaxAragon = 0.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stats|Enemy")
		bool bWasScanned = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stats|Data")
		FString CharacterName;

	//What is the player's current power 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats|Powers")
		TEnumAsByte<ESuitMainAbilities> CurrentSuitPower;

	//What is the player's First Power Modifier
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats|Powers")
		TEnumAsByte<ESuitPowerModifiers> PowerModifierSlotOne;

	//What is the player's Second Power Modifier
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats|Powers")
		TEnumAsByte<ESuitPowerModifiers> PowerModifierSlotTwo;

	//The player's current Quicksilver Stats
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats|Ability")
		struct FPlayerMainAbilityData QuicksilverStats;
	
	//The player's current Showstopper Stats
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats|Ability")
		struct FPlayerMainAbilityData ShowstopperStats;
	
	//The player's current Overload Stats
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats|Ability")
		struct FPlayerMainAbilityData OverloadStats;

	//The player's current Dash Rush Stats
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats|Ability")
		struct FPlayerPowerModifierData DashRushStats;

	//The player's current Overload Stats
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats|Ability")
		struct FPlayerPowerModifierData JumpBlastStats;

	//This will track what abilities the player should have unlocked
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stats|Powers")
		TMap<FString, bool> PlayerPowerUnlockMap;

	//This returns the owner's current power
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Stats|Data")
		ESuitMainAbilities GetCurrentPower();

	//This returns the owner's current health
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Stats|Data")
		float GetCurrentHealth();

	//This returns the owner's max health
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Stats|Data")
		float GetMaxHealth();

	//This returns the owner's current health percentage
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Stats|Data")
		float GetHealthPercentage();

	//This returns the owner's current Aragon
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Stats|Data")
		float GetCurrentAragon();

	//This returns the owner's max Aragon
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Stats|Data")
		float GetMaxAragon();

	//This returns the owner's current Aragon percentage
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Stats|Data")
		float GetAragonPercentage();

	//This function will add the @param IncreaseAmount to the owner's Max Health, then reset the Current Health 
	UFUNCTION(BlueprintCallable, Category = "Stats|Upgrade")
		void UpgradeHealthStats(float IncreaseAmount);

	//This function will add the @param IncreaseAmount to the owner's Max Aragon, then reset the Current Aragon
	UFUNCTION(BlueprintCallable, Category = "Stats|Upgrade")
		void UpgradeAragonStats(float IncreaseAmount);

	//This function will directly set MaxHealth to @param NewHealthAmount, then reset Current Health
	UFUNCTION(BlueprintCallable, Category = "Stats|Upgrade")
		void UpdateMaxHealth(float NewHealthAmount);

	//This function will directly set MaxAragon to @param NewAragonAmount, then reset Current Aragon
	UFUNCTION(BlueprintCallable, Category = "Stats|Upgrade")
		void UpdateMaxAragon(float NewAragonAmount);

	//This function will decrease the @param ConsumeAmount to the owner's Current Aragon
	UFUNCTION(BlueprintCallable, Category = "Stats|Upgrade")
		void ConsumeAragon(float ConsumeAmount);

	//This function will add to the owner's Current Aragon - for timer
	UFUNCTION(BlueprintCallable, Category = "Stats|Aragon")
		void RechargeAragon();

	//This function will decrease the owner's Current Health
	UFUNCTION(BlueprintCallable, Category = "Stats|Health")
		void DamageHealth(float DecreaseAmount);

	//This function will increase the owner's Current Health, up to their Max Health
	UFUNCTION(BlueprintCallable, Category = "Stats|Health")
		void RecoverHealth(float RecoverAmount);

	//Is the owner's Current Health less than or equal to 0?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		bool bIsDead = false;

	//Is the owner's Current Aragon less than or equal to 0?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats|Power")
		bool bIsAragonEmpty = false;

	//Is the owner's Current Aragon recharging?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats|Power")
		bool bIsRecharging = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		UDataTable* MainAbilityDataTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		UDataTable* PowerModifierDataTable;


};
