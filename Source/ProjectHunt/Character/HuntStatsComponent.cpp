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
	UI_CurrentHealth = StatsData.CurrentHealth;
	return UI_CurrentHealth;
}

float UHuntStatsComponent::GetPlayerMaxHealth()
{
	UI_MaxHealth = StatsData.MaxHealth;
	return UI_MaxHealth;
}

float UHuntStatsComponent::GetPlayerCurrentAragon()
{
	UI_CurrentAragon = StatsData.CurrentAragon;
	return UI_CurrentAragon;
}

float UHuntStatsComponent::GetPlayerMaxAragon()
{
	UI_MaxAragon = StatsData.MaxAragon;
	return UI_MaxAragon;
}

