// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ProjectHunt : ModuleRules
{
	public ProjectHunt(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "UMG", "Slate", "SlateCore", "RenderCore", "GameplayTasks", "AIModule" });
        PrivateDependencyModuleNames.AddRange(new string[] { "OnlineSubsystem" });
        if (Target.Platform == UnrealTargetPlatform.Android)
        {
            PrivateDependencyModuleNames.AddRange(new string[] { "OnlineSubsystem", "OnlineSubsystemUtils" });
            DynamicallyLoadedModuleNames.Add("AndroidAdvertising");
            DynamicallyLoadedModuleNames.AddRange(new string[] { "OnlineSubsystemGooglePlay" });
        }

    }
}
