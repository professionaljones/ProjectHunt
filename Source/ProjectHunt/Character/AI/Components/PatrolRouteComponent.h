// Copyright 2020 Brandon Jones. All Rights Reserved.

#pragma once
#include "Components/ActorComponent.h"
#include "PatrolRouteComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PROJECTHUNT_API UPatrolRouteComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	TArray<AActor*> GetPatrolPoints() const;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Patrol Route")
		TArray<AActor*> PatrolPoints;

};
