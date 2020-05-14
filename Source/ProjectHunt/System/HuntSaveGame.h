// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "ProjectHunt/Character/HuntStatsComponent.h"
#include "HuntSaveGame.generated.h"

/**
 *
 */
UCLASS()
class PROJECTHUNT_API UHuntSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UHuntSaveGame();

	UPROPERTY(VisibleAnywhere, Category = Basic)
		FString SaveSlotName;

	UPROPERTY(VisibleAnywhere, Category = Basic)
		FString PlayerName;

	UPROPERTY(VisibleAnywhere, Category = Basic)
		uint32 UserIndex;

	UPROPERTY(VisibleAnywhere, Category = "Player|Stats")
		float SavedCurrentPlayerHealth;

	UPROPERTY(VisibleAnywhere, Category = "Player|Stats")
		float SavedMaxPlayerHealth;

	UPROPERTY(VisibleAnywhere, Category = "Player|Stats")
		float SavedCurrentPlayerAragon;

	UPROPERTY(VisibleAnywhere, Category = "Player|Stats")
		float SavedMaxPlayerAragon;

	UPROPERTY(VisibleAnywhere, Category = "Player|Inventory")
		TMap<int, class AHuntWeapon*> SavedPlayerInventory;

	


	float GetPlayerCurrentHealth();

	float GetPlayerMaxHealth();



};
