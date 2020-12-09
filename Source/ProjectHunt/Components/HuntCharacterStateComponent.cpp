// Copyright 2020 Brandon Jones. All Rights Reserved.


#include "HuntCharacterStateComponent.h"

// Sets default values for this component's properties
UHuntCharacterStateComponent::UHuntCharacterStateComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UHuntCharacterStateComponent::SetNewState(TEnumAsByte<ECharacterState> newState)
{
	currentState = newState;
}

// Called when the game starts
void UHuntCharacterStateComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UHuntCharacterStateComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

