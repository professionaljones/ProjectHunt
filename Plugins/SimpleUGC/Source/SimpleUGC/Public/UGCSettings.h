// Copyright 2020 Brandon Jones. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "UGCSettings.generated.h"

/**
 *
 */
UCLASS(config = EditorUserSettings, defaultconfig)
class SIMPLEUGC_API UUGCSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UUGCSettings();

	// Config ini file (without extension) that settings are saved to.
	// Requires engine restart for changes to take effect.
	UPROPERTY(Config, EditAnywhere, Category = Settings)
		FString SettingsIniName = "Settings";


protected:
	/**
	 * The category name to use, overrides the one detected by looking at the config=... class metadata.
	 * Arbitrary category names are not supported, this must map to an existing category we support in the settings
	 * viewer.
	 */
	FName CategoryName;

	/** The Section name, is the short name for the settings.  If not filled in, will be the FName of the class. */
	FName SectionName;
};
