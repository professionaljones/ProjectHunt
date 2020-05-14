// Fill out your copyright notice in the Description page of Project Settings.


#include "HuntStatsComponent.h"

// Sets default values for this component's properties
UHuntStatsComponent::UHuntStatsComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	bEditableWhenInherited = true;
	// ...
}


// Called when the game starts
void UHuntStatsComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UHuntStatsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

float UHuntStatsComponent::GetPlayerCurrentHealth()
{
	UI_CurrentHealth = CurrentHealth;
	return UI_CurrentHealth;
}

float UHuntStatsComponent::GetPlayerMaxHealth()
{
	UI_MaxHealth = MaxHealth;
	return UI_MaxHealth;
}

float UHuntStatsComponent::GetPlayerCurrentAragon()
{
	UI_CurrentAragon = CurrentAragon;
	return UI_CurrentAragon;
}

float UHuntStatsComponent::GetPlayerMaxAragon()
{
	UI_MaxAragon = MaxAragon;
	return UI_MaxAragon;
}

void UHuntStatsComponent::UpgradeHealthStats(float IncreaseAmount)
{
	MaxHealth = MaxHealth + IncreaseAmount;
	CurrentHealth = MaxHealth;
}

void UHuntStatsComponent::UpgradeAragonStats(float IncreaseAmount)
{
	MaxAragon = MaxAragon + IncreaseAmount;
	CurrentAragon = MaxAragon;
}

void UHuntStatsComponent::ConsumeAragon(float ConsumeAmount)
{
	CurrentAragon -= ConsumeAmount;
	if (CurrentAragon <= MaxAragon)
	{
		bIsRecharging = true;
	}
	if (CurrentAragon <= 0)
	{
		bIsAragonEmpty = true;
		
	}
}

void UHuntStatsComponent::RechargeAragon()
{
	CurrentAragon += AragonRechargeAmount;
	if (CurrentAragon >= MaxAragon)
	{
		CurrentAragon = MaxAragon;
		bIsRecharging = false;
	}
}

