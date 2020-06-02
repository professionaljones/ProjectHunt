// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Weapons/HuntWeapon.h"
#include "Character/HuntStatsComponent.h"
#include "ProjectHunt/Character/Player/HuntPlayerController.h"
#include "ProjectHunt/Character/HuntCharacterInterface.h"
#include "ProjectHuntCharacter.generated.h"

class UInputComponent;
//class UHuntStatsComponent;


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

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Mesh)
		class USkeletalMeshComponent* Mesh1P;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FirstPersonCameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Stats, meta = (AllowPrivateAccess = "true"))
		class UHuntStatsComponent* StatsComponent;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Weapon)
		class AHuntWeapon* CurrentWeapon;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Player", meta = (AllowPrivateAccess = "true"))
		class AHuntPlayerController* MyPlayerController;

	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Audio, meta = (AllowPrivateAccess = "true"))
		class UAudioComponent* CharacterAudioComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Audio)
		class UAudioComponent* SuitAudioComponent;


protected:
	virtual void BeginPlay();

public:
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
		float DamageTakenModifier = 1.0f;

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character|Data")
		int32 CurrentDataPoints = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character|Data")
		int32 MaxDataPoints = 99999999;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character|Data")
		int32 DataPointsToAdd = 0;

	//This function can be used to increase or decrease the player's style amount
	UFUNCTION(BlueprintCallable, Category = "Player|Style")
		void ModifyDataPoints(int32 NewDataPoints);

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

	

	FTimerHandle StyleDecreaseTimer;

protected:

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
	/** Returns Mesh1P subobject **/
	FORCEINLINE class USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

	

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

