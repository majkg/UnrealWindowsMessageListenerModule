// Copyright (c) 2025, Michael Golembewski. All rights reserved.

/**
 * This file defines the build rules for the WindowsMessageListener module.
 * It specifies dependencies, include paths, and other build settings.
 */

using UnrealBuildTool;
using System.IO;

public class WindowsMessageListener : ModuleRules
{
    public WindowsMessageListener(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] 
        { 
            "Core", 
            "CoreUObject", 
            "Engine", 
            "InputCore",
            "ApplicationCore",
            "Slate",
            "SlateCore",
            "UnrealEd" // Added for testing support
        });

        PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "Public")); // Public headers for external modules
        PrivateIncludePaths.Add(Path.Combine(ModuleDirectory, "Private")); // Private headers for internal use
    }
}