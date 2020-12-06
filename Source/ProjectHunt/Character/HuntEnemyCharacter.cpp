// Copyright 2020 Brandon Jones. All Rights Reserved.


#include "HuntEnemyCharacter.h"

AHuntEnemyCharacter::AHuntEnemyCharacter()
{
	//Create a StatsComponent
	StatsComponent = CreateDefaultSubobject<UHuntStatsComponent>("StatsComponent");
}

void AHuntEnemyCharacter::CharacterTakeDamage(float DamageAmount)
{
	StatsComponent->DamageHealth(DamageAmount * DamageTakenModifier);
	if (StatsComponent->bIsDead)
	{
		StatsComponent->OnDeathDelegate.Broadcast();
	}
}

bool AHuntEnemyCharacter::IsCharacterDead()
{
	return StatsComponent->bIsDead;
}
