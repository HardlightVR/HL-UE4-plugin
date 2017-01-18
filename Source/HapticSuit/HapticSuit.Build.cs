// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.IO;
using System;

public class HapticSuit : ModuleRules
{
	public HapticSuit(TargetInfo Target)
	{
        var HapticSuitPath = Path.GetFullPath(Path.Combine(ModuleDirectory, "../ThirdParty/"));
        var libPath = Path.Combine(HapticSuitPath, "lib");

	    switch (Target.Platform)
	    {
            case UnrealTargetPlatform.Win64:
                PublicAdditionalLibraries.Add(Path.Combine(libPath, "x64", "NSLoader.lib"));
	            break;

            case UnrealTargetPlatform.Win32:
	            PublicAdditionalLibraries.Add(Path.Combine(libPath, "x86", "NSLoader.lib"));
	            break;
	    }

        PublicIncludePaths.AddRange(
			new string[] {
				"HapticSuit/Public"
            }
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				"HapticSuit/Private",
                "ThirdParty/include"
            }
            );
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
                "CoreUObject",
                "Engine",
				"Projects"
			}
			);

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "CoreUObject",
                "Engine",
                "Projects"
            }
            );
    }
}
