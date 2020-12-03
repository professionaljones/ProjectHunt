// Copyright 2020 Brandon Jones. All Rights Reserved.


#include "PlayerStatsComponent.h"
#include "Kismet/KismetTextLibrary.h"

float UPlayerStatsComponent::GetPlayerItemCollectionRate()
{
	return fCurrentItemCollectionPercentage / fMaxItemCollectionPercentage;
}

FText UPlayerStatsComponent::GetPlayerItemCollectionRateAsText()
{
	return UKismetTextLibrary::AsPercent_Float(fCurrentItemCollectionPercentage, ERoundingMode::FromZero, false, true, 1, 324, 0, 3);
}
