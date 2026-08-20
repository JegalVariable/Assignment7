// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Assignment7 : ModuleRules
{
	public Assignment7(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
