// Copyright 2020 Brandon Jones. All Rights Reserved.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "HuntSystemFunctionLibrary.generated.h"

class UHuntSaveGame;

/**
 *
 */
UCLASS()
class PROJECTHUNT_API UHuntSystemFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	//Returns the project version set in the 'Project Settings' > 'Description' section of the editor
	UFUNCTION(BlueprintPure, Category = "Project")
		static FString GetProjectVersion();

	//Returns the project name set in the 'Project Settings' > 'Description' section of the editor
	UFUNCTION(BlueprintPure, Category = "Project")
		static FString GetProjectName();

};
