// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class GuardiansOfGame : ModuleRules
{
	public GuardiansOfGame(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "UMG", "AIModule", "NavigationSystem", "ApexDestruction", "Niagara", "GameplayCameras" });

		PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
	}
}
