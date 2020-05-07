// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "Runtime/Core/Public/Serialization/Archive.h"
#include "HuntStatsComponent.generated.h"



USTRUCT(BlueprintType)
struct FCharacterStats : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, SaveGame, Category = "Stats|Health")
		float CurrentHealth = 0.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, SaveGame, Category = "Stats|Health")
		float MaxHealth = 100.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, SaveGame, Category = "Stats|Aragon")
		float CurrentAragon = 0.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, SaveGame, Category = "Stats|Aragon")
		float MaxAragon = 0.0f;
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

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stats")
		struct FCharacterStats StatsData;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats|Health")
		float UI_CurrentHealth = 0.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats|Health")
		float UI_MaxHealth = 100.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats|Aragon")
		float UI_CurrentAragon = 0.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats|Aragon")
		float UI_MaxAragon = 0.0f;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Player|Data")
		float GetPlayerCurrentHealth();
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Player|Data")
		float GetPlayerMaxHealth();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Player|Data")
		float GetPlayerCurrentAragon();
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Player|Data")
		float GetPlayerMaxAragon();


};
