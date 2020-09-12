// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SkeletalMeshComponent.h"
#include "ProjectHunt/ProjectHunt.h"
#include "Particles/ParticleSystem.h"
#include "HuntWeaponInterface.h"
#include "HuntWeaponProjectile.h"
#include "Components/AudioComponent.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "HuntWeapon.generated.h"

//What kind of weapon is this
UENUM(BlueprintType)
enum EWeaponType
{
	WT_Unequipped UMETA(DisplayName = "Unequipped"),
	WT_Explosive UMETA(DisplayName = "Explosives"),
	WT_Pistol UMETA(DisplayName = "Pistol"),
	WT_SMG UMETA(DisplayName = "SMG"),
	WT_Rifle UMETA(DisplayName = "Rifle"),
	WT_Shotgun UMETA(DisplayName = "Shotgun"),
	WT_RocketLauncher UMETA(DisplayName = "Rocket Launcher"),
	WT_Sniper UMETA(DisplayName = "Sniper Rifle")
};

//What kind of projectile does this weapon use
UENUM(BlueprintType)
enum EProjectileType
{
	//No projectile used
	PT_None UMETA(DisplayName = "None"),
	//Use this for weapons that would directly hit the target
	PT_Instant UMETA(DisplayName = "Instant"),
	//Use this for weapons that require the user to make contact with the target
	PT_Projectile UMETA(DisplayName = "Projectile"),
	//Unused for now
	PT_Special,
};


//What ammo does this weapon use
UENUM(BlueprintType, meta = (Bitflags))
enum EAmmoType
{
	AT_None UMETA(DisplayName = "None"),
	AT_Standard UMETA(DisplayName = "Standard"),
	AT_Fire UMETA(DisplayName = "Incendiary"),
	AT_Ice UMETA(DisplayName = "Ice"),
	AT_Shock UMETA(DisplayName = "Shock"),
	AT_Aragon UMETA(DisplayName = "Aragon")
};

//What form of projectile should spawn when we fire
UENUM(BlueprintType)
enum EProjectileState
{
	Projectile_None,
	Projectile_Normal UMETA(DisplayName = "Standard Projectile"),
	Projectile_Charge UMETA(DisplayName = "Charged Projectile"),
	Projectile_Alt UMETA(DisplayName = "Alternate Projectile"),
	Projectile_ChargeAlt UMETA(DisplayName = "Charged Alternate"),
	Projectile_Laser
};

//This is the data for this weapon (base damage, ammo, etc)
USTRUCT(BlueprintType)
struct FWeaponStatsData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:

	//We use this to determine the slot the weapon should fill in the inventory
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon|Data")
		TEnumAsByte<EWeaponType> WeaponType;

	//This weapon's Ammo Type
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo|Type")
		TEnumAsByte<EAmmoType> WeaponAmmoType;



	//What is the damage level of this weapon
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Stats|Level")
		int32 WeaponDamageLevel = 1;

	//What is the fire rate level of this weapon
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Stats|Level")
		int32 FireRateLevel = 1;

	//What is the fire rate level of this weapon
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Stats|Level")
		int32 ChargeRateLevel = 1;

	//What is the fire rate level of this weapon
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Stats|Level")
		int32 ChargeLimitLevel = 1;


	//What is the maximum level of this weapon?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame, Category = "Weapon|Stats|Level")
		int32 MaxWeaponLevel = 5;

	//How fast does this weapon fire - if it is automatic
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
		float FireRate;

	//How fast does this weapon fire - if it is automatic
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
		float ChargeRate;


	////End Ammo

	///// Damage


	//How much damage does this weapon do, without any modifiers
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Damage")
		float BaseDamage = 0.0f;
	//Are there any bonus to damage before Quicksilver or Overdrive? Otherwise, leave at 1
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Damage")
		float DamageMultiplierAmount = 0.0f;


	//When in Quicksilver or Overdrive, how much should the damage be multiplied by ?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Damage")
		float DamageModifierAmount = 0.0f;

	//Give us the sum/product of BaseDamage and DamageMultiplier
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Damage")
		float TotalDamage = 0.0f;

	//Give us the sum/product of BaseDamage and CritMultiplier
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Damage")
		float CriticalHitDamage = 0.0f;

	//When in Quicksilver or Overdrive, how much should the damage be multiplied by?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Damage|Modifiers")
		float SpecialDamageMultiplier = 0.0f;

	//When the player hits an enemy at a weak point (IE Headshot), how much additional damage should the player deal
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Damage|Modifiers")
		float CriticalHitMultiplier = 0.0f;

	//Store the original damage amount for resetting
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Damage|Reset")
		float OriginalBaseDamageAmount = 0.0f;

	//Store the original DamageMultiplier for resetting
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Damage|Reset")
		float OriginalDamageMultiplier = 0.0f;

	//Store the original DamageModifier for resetting
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage|Reset")
		float OriginalDamageModifier = 0.0;

	////End Damage


	////Start Charge

	//How much can this weapon charge up to
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame, Category = "Charge")
		float WeaponChargeLimit;

	//How much of a delay before the weapon begins to charge
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame, Category = "Charge")
		float WeaponChargeDelay;

};
/**
 * This is for getting the data for Weapon upgrades
 */
USTRUCT(BlueprintType)
struct FWeaponUpgradeData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:

	//What is the new damage level of this weapon
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Upgrade")
		int32 WeaponDamageLevel;

	//How much additional damage gained at this level
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Upgrade")
		float DamageUpgradeAmount;

	//What is the price of this upgrade?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Upgrade")
		float DamageUpgradePrice;

	//What is the new fire rate level of this weapon
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Upgrade")
		int32 FireRateLevel;

	//How much faster can this weapon fire?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Upgrade")
		float FireRateUpgradeAmount;

	//What is the price of this upgrade?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Upgrade")
		float FireRateUpgradePrice;

	//What is the charge rate level of this weapon
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Upgrade")
		int32 ChargeRateLevel;

	//How much faster can charge weapons charge?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Upgrade")
		float ChargeRateAmountIncrease;

	//What is the price of this upgrade?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Upgrade")
		float ChargeRateUpgradePrice;

	//What is the new fire rate level of this weapon
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Upgrade")
		int32 ChargeLimitLevel;

	//What is the new maximum limit for charge weapons
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Upgrade")
		float ChargeLimitAmountIncrease;

	//What is the price of this upgrade?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Upgrade")
		float ChargeLimitUpgradePrice;

	
};

UCLASS()
class PROJECTHUNT_API AHuntWeapon : public AActor, public IHuntWeaponInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AHuntWeapon();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class AHuntWeaponProjectile* ProjectileToSpawn = NULL;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
		TEnumAsByte<EProjectileType> WeaponProjectile;

	//This weapon's Ammo Type
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo|Type")
		TEnumAsByte<EAmmoType> OriginalAmmoType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
		TEnumAsByte<EProjectileState> WeaponProjectileState;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ammo|Projectiles")
		TMap<TEnumAsByte<EProjectileState>, TSubclassOf<AHuntWeaponProjectile>> WeaponProjectiles;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		bool bCanWeaponCharge;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Charge")
		bool bIsCharging;

	//Is this weapon automatic?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		bool bIsAutomatic;

	//Empty to hold weapon charge
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Charge")
		float CurrentWeaponCharge;

	//How much to charge the weapon by
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Charge")
		float AmountToCharge;

	//What is the name of the socket that this weapon attaches to
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Data")
		FName WeaponAttachPoint;

	//Mainly for VFX - can also be used to spawn projectiles
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Data")
		FName WeaponMuzzlePoint;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		UDataTable* WeaponUpgradeDataTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		UDataTable* WeaponStatsTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		struct FWeaponStatsData WeaponStatsData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		struct FWeaponUpgradeData WeaponUpgradeData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		TMap<int32, FName> WeaponLevelMap;

	//Start Feedback

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Feedback|Debug")
		bool bEnableDebugMode = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Feedback|Visual")
		class UParticleSystem* WeaponFireVFX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Feedback|Audio")
		class USoundBase* WeaponFireSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Feedback|Audio")
		class USoundBase* WeaponChargeFireSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Feedback|Audio")
		class USoundBase* WeaponChargingSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Feedback|Audio")
		class USoundBase* WeaponAltFireSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Feedback|Audio")
		class USoundBase* WeaponEquipSound;




	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Targets")
		TArray<TEnumAsByte<EObjectTypeQuery>> ObjectsToTarget;



	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon|Targets")
		TArray<AActor*> ActorsToIgnore;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon|Data")
		int32 WeaponInventorySlot = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		FHitResult SingleHit;

	UPROPERTY(BlueprintReadOnly)
		FVector MyLocation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Data")
		FVector StartLocation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Data")
		FVector EndLocation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		TArray<FHitResult> Hits;


	////End Feedback
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Data")
		FTimerHandle AutoFireTimer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Data")
		FTimerHandle ChargeFireTimer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Data")
		FTimerHandle ResetDamageTimer;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon|Data")
		class AProjectHuntCharacter* WeaponOwner;


public:

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Called when the player/AI want to fire the weapon
	UFUNCTION()
		void FireWeapon();

	//Called when the player/AI want to fire the weapon
	UFUNCTION()
		void FireCharge();

	//Called when the player/AI needs to reset damage and charge
	UFUNCTION(BlueprintCallable, Category = "Weapon")
		void ResetCharge();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
		void CalculateDamage();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
		void CalculateCritDamage();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
		void CalculateSpecialDamage();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
		void ResetDamage();

	UFUNCTION(BlueprintCallable,BlueprintPure, Category = "Weapon")
		EAmmoType GetWeaponAmmoType();

	UFUNCTION()
		void SpawnWeaponProjectile();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
		void StartFire();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
		void EndFire();

	UFUNCTION()
		void StartCharge();

	UFUNCTION()
		void Charge();

	UFUNCTION()
		void FinishCharge();

	void AttachToOwner();

	UFUNCTION(BlueprintCallable, Category = "Weapon|Data")
		void SetWeaponOwner(AProjectHuntCharacter* NewOwner);

	UFUNCTION(BlueprintCallable, Category = "Weapon|Data")
		void SetWeaponStats(FWeaponStatsData NewWeaponStats);

	UFUNCTION(BlueprintCallable, Category = "Weapon|Data")
		void UpgradeDamage(float IncreaseAmount);

	UFUNCTION(BlueprintCallable, Category = "Weapon|Data")
		void UpgradeFireRate(float IncreaseAmount);

	UFUNCTION(BlueprintCallable, Category = "Weapon|Data")
		void UpgradeChargeRate(float IncreaseAmount);

	UFUNCTION(BlueprintCallable, Category = "Weapon|Data")
		void UpgradeChargeLimit(float IncreaseAmount);

	UFUNCTION(BlueprintCallable, Category = "Weapon|Data")
		void UpgradeDamageMultiplier(float IncreaseAmount);

	UFUNCTION(BlueprintCallable, Category = "Weapon|Data")
		void UpgradeDamageModifier(float IncreaseAmount);

	UFUNCTION(BlueprintCallable, Category = "Weapon|Data")
		void ResetDamageMultiplier();

	UFUNCTION(BlueprintCallable, Category = "Weapon|Data")
		void ResetDamageModifier();

	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UAIPerceptionStimuliSourceComponent* MyStimuliSourceComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		USkeletalMeshComponent* WeaponMeshFP;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		USkeletalMeshComponent* WeaponMeshTP;

	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly, Category = "Weapon|SFX")
		UAudioComponent* WeaponAudioComponent;

	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly, Category = "Weapon|SFX")
		UAudioComponent* WeaponAltAudioComponent;

};
