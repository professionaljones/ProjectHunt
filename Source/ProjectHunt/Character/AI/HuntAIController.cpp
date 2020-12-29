// Copyright 2020 Brandon Jones. All Rights Reserved.


#include "HuntAIController.h"

AHuntAIController::AHuntAIController()
{
	SetGenericTeamId(FGenericTeamId(TeamId));
	//MyAIPerceptionSystem = CreateDefaultSubobject<UAIPerceptionSystem>("PerceptionComponent");
}

ETeamAttitude::Type AHuntAIController::GetTeamAttitudeTowards(const AActor& Other) const
{
	if (const APawn* OtherPawn = Cast<APawn>(&Other)) {

		if (const IGenericTeamAgentInterface* TeamAgent = Cast<IGenericTeamAgentInterface>(OtherPawn->GetController()))
		{
			//Other controllers with an ID of 5 are Friendly
			FGenericTeamId OtherTeamID = TeamAgent->GetGenericTeamId();
			if (OtherTeamID == 5)
			{
				return ETeamAttitude::Friendly;
			}
			//Controllers with an ID of 18 are Hostile - the player
			if (OtherTeamID == 18)
			{
				return ETeamAttitude::Hostile;
			}
			//Controllers with an ID of 10 are Neutral
			if (OtherTeamID == 10)
			{
				return ETeamAttitude::Neutral;
			}
		}
	}

	return ETeamAttitude::Neutral;
}

