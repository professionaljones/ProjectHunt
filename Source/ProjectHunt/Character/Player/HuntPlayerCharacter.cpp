// Fill out your copyright notice in the Description page of Project Settings.


#include "HuntPlayerCharacter.h"

AHuntPlayerCharacter::AHuntPlayerCharacter()
{
	StatsComponent->StatsData.MaxHealth = 200;
	StatsComponent->StatsData.MaxAragon = 200;
	StatsComponent->StatsData.CurrentHealth = StatsComponent->StatsData.MaxHealth;
	StatsComponent->StatsData.CurrentAragon = StatsComponent->StatsData.MaxAragon;
	MaxStyleAmount = D_StyleLimit;
}

