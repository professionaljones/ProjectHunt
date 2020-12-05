// Copyright 2020 Brandon Jones. All Rights Reserved.

#pragma once

#include "UObject/Interface.h"
#include "Misc/Guid.h"
#include "HuntSaveableObjectInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UHuntSaveableObjectInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROJECTHUNT_API IHuntSaveableObjectInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Saveable Object")
	void GetObjectSaveableValues(FGuid ObjectID, bool bWasInteractedWith = false);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Saveable Object")
	void DidPlayerInteractWithObject(bool bWasInteracted = false);
};
