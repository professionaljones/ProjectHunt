// Fill out your copyright notice in the Description page of Project Settings.


#include "HuntPlayerCharacter.h"

AHuntPlayerCharacter::AHuntPlayerCharacter()
{
	StatsComponent->MaxHealth = 200;
	StatsComponent->MaxAragon = 200;
	StatsComponent->CurrentHealth = StatsComponent->MaxHealth;
	StatsComponent->CurrentAragon = StatsComponent->MaxAragon;
	MaxStyleAmount = SSS_StyleLimit;
}

int32 AHuntPlayerCharacter::GetJumpCount()
{
	return JumpCount;
}

int32 AHuntPlayerCharacter::GetDashCount()
{
	return DashCount;
}



