// Copyright 2020 Brandon Jones. All Rights Reserved.


#include "PatrolRouteComponent.h"
#include "ProjectHunt/ProjectHunt.h"

//GetPatrolPoints
TArray<AActor*> UPatrolRouteComponent::GetPatrolPoints() const
{
	return PatrolPoints;
}
