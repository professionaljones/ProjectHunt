// Copyright 2020 Brandon Jones. All Rights Reserved.

#pragma once

#include "ProjectHunt/ProjectHuntCharacter.h"
#include "ProjectHunt/Character/HuntStatsComponent.h"
#include "HuntEnemyCharacter.generated.h"

/**
 *
 */
UCLASS()
class PROJECTHUNT_API AHuntEnemyCharacter : public AProjectHuntCharacter
{
	GENERATED_BODY()

		AHuntEnemyCharacter();
public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Stats, meta = (AllowPrivateAccess = "true"))
		class UHuntStatsComponent* StatsComponent;

	virtual void CharacterTakeDamage(float DamageAmount) override;
	virtual bool IsCharacterDead() override;

protected:

public:


};
