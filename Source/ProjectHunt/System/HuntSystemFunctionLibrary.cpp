// Copyright 2020 Brandon Jones. All Rights Reserved.


#include "HuntSystemFunctionLibrary.h"
//#include "CoreGlobals.h"
#include "Misc/ConfigCacheIni.h"

FString UHuntSystemFunctionLibrary::GetProjectVersion()
{
	FString ProjectVersion;
	GConfig->GetString(
		TEXT("/Script/EngineSettings.GeneralProjectSettings"),
		TEXT("ProjectVersion"),
		ProjectVersion,
		GGameIni
	);
	return ProjectVersion;
}
