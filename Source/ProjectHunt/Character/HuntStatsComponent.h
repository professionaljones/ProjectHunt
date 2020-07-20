// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Runtime/Core/Public/Serialization/Archive.h"
#include "HuntStatsComponent.generated.h"

UENUM(BlueprintType)
enum ESuitMainAbilities
{
	MA_None UMETA(DisplayName = "Unequipped"),
	MA_Quicksilver UMETA(DisplayName = "Quicksilver"),
	MA_Showstopper UMETA(DisplayName = "Showstopper"),
	MA_Overload UMETA(DisplayName = "Overload")
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

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stats")
		FString CharacterName;

	//What is the player's current power 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats|Powers")
		TEnumAsByte<ESuitMainAbilities> CurrentSuitPower;

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

	//This function will decrease the @param ConsumeAmount to the owner's Current Aragon
	UFUNCTION(BlueprintCallable, Category = "Stats|Upgrade")
		void ConsumeAragon(float ConsumeAmount);

	//This function will add to the owner's Current Aragon - for timer
	UFUNCTION(BlueprintCallable, Category = "Stats|Upgrade")
		void RechargeAragon();

	//This function will decrease the owner's Current Health
	UFUNCTION(BlueprintCallable, Category = "Stats|Damage")
		void DamageHealth(float DecreaseAmount);

	//This function will increase the owner's Current Health, up to their Max Health
	UFUNCTION(BlueprintCallable, Category = "Stats|Damage")
		void RecoverHealth(float RecoverAmount);

	//Is the owner's Current Health less than or equal to 0?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats|Power")
		bool bIsDead = false;

	//Is the owner's Current Aragon less than or equal to 0?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats|Power")
		bool bIsAragonEmpty = false;

	//Is the owner's Current Aragon recharging?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats|Power")
		bool bIsRecharging = false;


};
