// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "ProjectHunt/ProjectHunt.h"
#include "GameFramework/Character.h"
//#include "Weapons/HuntWeapon.h"
#include "ProjectHunt/Character/HuntStatsComponent.h"
#include "ProjectHunt/Character/Player/HuntPlayerController.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "ProjectHunt/Character/HuntCharacterInterface.h"
#include "ProjectHuntCharacter.generated.h"

class UInputComponent;
class AHuntWeapon;


//What is the player's current style rank
UENUM(BlueprintType)
enum ECharacterStyleRank
{
	SR_Dull,
	SR_Crazy,
	SR_Blast,
	SR_Alright,
	SR_Showtime,
	SR_Stylish,
	SR_SuperStylish

};



UCLASS(config = Game)
class AProjectHuntCharacter : public ACharacter,public IHuntCharacterInterface
{
	GENERATED_BODY()

public:
	AProjectHuntCharacter();

	
	


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Weapon)
		class AHuntWeapon* CurrentWeapon;


	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Audio, meta = (AllowPrivateAccess = "true"))
		class UAudioComponent* CharacterAudioComponent;

	


protected:
	virtual void BeginPlay();

public:

	//How fast can the player move on land
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame, Category = "Movement|Walking")
		float MovementSpeed = 250.0f;

	//How fast can the player move on land
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame, Category = "Movement|Walking")
		float MovementSpeedModifier = 1.0f;

	//How fast should the Rush recharge increment by
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement|Dash")
		float RushRechargeAmount = 0.05f;


	//How long until the Rush count is incremented
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame, Category = "Movement|Dash")
		float RushRechargeLimit = 5.0f;

	//Value to modify to control Rush recharging - zero-filled on start
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Transient, Category = "Movement|Dash")
		float CurrentRushRecharge = 0.0f;

	//How fast should the dash recharge increment by
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement|Dash")
		float DashRechargeAmount = 0.01f;


	//How long until the dash count is incremented
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame, Category = "Movement|Dash")
		float DashRechargeLimit = 3.0f;

	//Value to modify to control dash recharging - zero-filled on start
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Transient, Category = "Movement|Dash")
		float CurrentDashRecharge = 0.0f;


	UFUNCTION(BlueprintCallable, Category = "Movement")
		float GetMovementSpeed();

	UFUNCTION(BlueprintCallable, Category = "Movement")
		void UpdateMovementSpeed(float NewMovementSpeed);

	UFUNCTION(BlueprintCallable, Category = "Movement")
		void UpdateMovementSpeedModifier(float NewMovementModifier);



	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseLookUpRate;



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		TArray<USoundBase*> DamageSounds;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		TArray<USoundBase*> DeathSounds;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Transient, Category = "Player|Style")
	TEnumAsByte<ECharacterStyleRank> PlayerStyle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats|Damage")
		float DamageTakenModifier = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats|Damage")
		float DamageDefenseModifer = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character|Data")
		float DamageRankModifier = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character|Data")
		float PlayerRankReference = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Transient, Category = "Player|Style")
		float StylePercentage = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Transient, Category = "Player|Style")
		float DamageStyleAmount = 3.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Transient, Category = "Player|Style")
		float CurrentStyleAmount = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player|Style")
		float MaxStyleAmount = 250.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player|Style")
		float StyleAmountMultiplier = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player|Style")
		float D_StyleLimit = 0.2f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player|Style")
		float C_StyleLimit = 0.40f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player|Style")
		float B_StyleLimit = 0.60f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player|Style")
		float A_StyleLimit = 0.85f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player|Style")
		float S_StyleLimit = 0.90f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player|Style")
		float SS_StyleLimit = 1.50f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player|Style")
		float SSS_StyleLimit = 2.50f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame, Category = "Character|Data")
		int32 CurrentDataPoints = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character|Data")
		int32 UI_CurrentDataPoints = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character|Data")
		float Cached_MouseSensitivityX = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character|Data")
		float Cached_MouseSensitivityY = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character|Data")
		float Cached_GamepadSensitivityX = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character|Data")
		float Cached_GamepadSensitivityY = 0.0f;



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character|Data")
		int32 MaxDataPoints = 99999999;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character|Data")
		int32 DataPointsToAdd = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character|Data")
		int ArenaPointsToAdd = 0;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Player|Style")
		int32 GetDataPoints();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Player|Style")
		int GetArenaPointsToAdd();


	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Character")
		bool bEnableMovementInput = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
		bool bEnableLookInput = true;


	//This function can be used to increase or decrease the player's data points
	UFUNCTION(BlueprintCallable, Category = "Player|Style")
		void ModifyDataPoints(int32 NewDataPoints);

	//This function can be used to directly set the player's data points
	UFUNCTION(BlueprintCallable, Category = "Player|Style")
		void UpdateDataPoints(int32 NewDataPoints);

	//This function can be used to increase or decrease the player's style amount
	UFUNCTION(BlueprintCallable,Category = "Player|Style")
		void ModifyStyle(float StyleModAmount);

	//This function can be used to decrease the player's style amount
	UFUNCTION(BlueprintCallable, Category = "Player|Style")
		void DecreaseStyle();

	UFUNCTION(BlueprintCallable, Category = "Player|Style")
		void UpdateStylePercentage();

	UFUNCTION(BlueprintCallable, Category = "Player|Style")
		void StartStyleModTimer();

	UFUNCTION(BlueprintCallable,BlueprintPure, Category = "Player|Style")
	float GetStylePercentage();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Player|Style")
		float GetCurrentStyleAmount();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Weapon")
		class AHuntWeapon* GetCurrentWeapon();

	//This will modify DamageDefenseModifer
	UFUNCTION(BlueprintCallable, Category = "Character|Data")
		void SetDamageDefenseModifer(float NewDefenseMod);

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent, Category = "Character|Stats")
	void ReactToDamage(AHuntWeapon* WeaponUsed);

	virtual void CharacterTakeDamage(float DamageAmount);

	virtual bool IsCharacterDead();

	UFUNCTION(BlueprintCallable, Category = "Aragon")
	virtual void CharacterActivatePower();

	UFUNCTION(BlueprintCallable, Category = "Aragon")
	virtual void CharacterDeactivatePower();

	UFUNCTION(BlueprintCallable, Category = "Aragon")
	virtual void CharacterRechargeAragon();
	

	FTimerHandle StyleDecreaseTimer;

protected:

	//List of sockets where when hit, character should take critical damage
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats|Damage")
		TArray<FName> CriticalHitLocations;

	/** Fires a projectile. */
	void OnFire();

	/** Fires a charged projectile if weapon can charge. */
	void OnFireEnd();


	/** Handles moving forward/backward */
	void MoveForward(float Val);

	/** Handles stafing movement, left and right */
	void MoveRight(float Val);

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnCharacter(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtCamera(float Rate);

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	struct TouchData
	{
		TouchData() { bIsPressed = false; Location = FVector::ZeroVector; }
		bool bIsPressed;
		ETouchIndex::Type FingerIndex;
		FVector Location;
		bool bMoved;
	};
	void BeginTouch(const ETouchIndex::Type FingerIndex, const FVector Location);
	void EndTouch(const ETouchIndex::Type FingerIndex, const FVector Location);
	void TouchUpdate(const ETouchIndex::Type FingerIndex, const FVector Location);
	TouchData	TouchItem;

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface

	/*
	 * Configures input for touchscreen devices if there is a valid touch interface for doing so
	 *
	 * @param	InputComponent	The input component pointer to bind controls to
	 * @returns true if touch controls were enabled.
	 */
	bool EnableTouchscreenMovement(UInputComponent* InputComponent);

public:
	

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UAIPerceptionStimuliSourceComponent* MyStimuliSourceComponent;
	

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

