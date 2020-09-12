// Copyright 2020 Brandon Jones. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "GenericTeamAgentInterface.h"
#include "Perception/AIPerceptionComponent.h"
#include "HuntAIController.generated.h"

/**
 *
 */
UCLASS()
class PROJECTHUNT_API AHuntAIController : public AAIController
{
	GENERATED_BODY()

		AHuntAIController();
public:
	//This function helps determine how we respond to something that we've heard or seen
	ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;

	//What is our Team
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Perception")
		FGenericTeamId TeamId;

	/*UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UAIPerceptionSystem* MyAIPerceptionSystem;*/
};
