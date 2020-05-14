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

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
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

	//How much health does the player currently have
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, SaveGame, Category = "Stats|Health")
		float CurrentHealth = 0.0f;

	//How much health does the player start with
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, SaveGame, Category = "Stats|Health")
		float MaxHealth = 100.0f;

	//How much Aragon does the player currently have
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, SaveGame, Category = "Stats|Aragon")
		float CurrentAragon = 0.0f;

	//How much Aragon does the player start with
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, SaveGame, Category = "Stats|Aragon")
		float MaxAragon = 0.0f;

	//How much Aragon does the player currently have
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, SaveGame, Category = "Stats|Aragon")
		float AragonRechargeAmount = 0.0f;


	//This is what the UI will report the player's Max Health is
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats|Health")
		float UI_CurrentHealth = 0.0f;

	//This is what the UI will report the player's Max Health is
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats|Health")
		float UI_MaxHealth = 100.0f;

	//This is what the UI will report the player's Current Aragon is
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats|Aragon")
		float UI_CurrentAragon = 0.0f;

	//This is what the UI will report the player's Max Aragon is
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats|Aragon")
		float UI_MaxAragon = 0.0f;

	//What is the player's current power 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats|Powers")
		TEnumAsByte<ESuitMainAbilities> CurrentSuitPower;

	//This will track what abilities the player should have unlocked
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stats|Powers")
		TMap<FString, bool> PlayerPowerUnlockMap;

	//This returns the player's current health
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Player|Data")
		float GetPlayerCurrentHealth();

	//This returns the player's max health
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Player|Data")
		float GetPlayerMaxHealth();

	//This returns the player's current Aragon
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Player|Data")
		float GetPlayerCurrentAragon();

	//This returns the player's max Aragon
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Player|Data")
		float GetPlayerMaxAragon();

	//This function will add the @param IncreaseAmount to the player's Max Health, then reset the Current Health 
	UFUNCTION(BlueprintCallable, Category = "Stats|Upgrade")
		void UpgradeHealthStats(float IncreaseAmount);

	//This function will add the @param IncreaseAmount to the player's Max Aragon, then reset the Current Aragon
	UFUNCTION(BlueprintCallable, Category = "Stats|Upgrade")
		void UpgradeAragonStats(float IncreaseAmount);

	//This function will decrease the @param ConsumeAmount to the player's Current Aragon
	UFUNCTION(BlueprintCallable, Category = "Stats|Upgrade")
		void ConsumeAragon(float ConsumeAmount);

	//This function will add to the player's Current Aragon - for timer
	UFUNCTION(BlueprintCallable, Category = "Stats|Upgrade")
		void RechargeAragon();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats|Power")
		bool bIsAragonEmpty = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats|Power")
		bool bIsRecharging = false;


};
