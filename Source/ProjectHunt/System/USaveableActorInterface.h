// Copyright 2020 Brandon Jones. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "USaveableActorInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UUSaveableActorInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROJECTHUNT_API IUSaveableActorInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Saveable Actor")
		void ActorSaveDataLoaded();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Saveable Actor")
		void ActorSaveDataSaved();
};
