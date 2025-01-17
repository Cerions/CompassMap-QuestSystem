// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class CompassMapProject : ModuleRules
{
	public CompassMapProject(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
