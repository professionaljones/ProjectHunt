// Copyright 2020 Brandon Jones. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/World.h"
#include "Engine.h"
#include "UGCContentSettings.generated.h"

/**
 * 
 */
UCLASS(config=UGCPluginSettings, Blueprintable, BlueprintType)
class PROJECTHUNT_API UUGCContentSettings : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(Config, BlueprintReadOnly)
		int32 test_number;
	UPROPERTY(Config, BlueprintReadOnly)
		FString test_string;

	UPROPERTY(Config)
		FString ProjectName;
	
};
