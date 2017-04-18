// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.IO;
using System;

public class HapticImporter : ModuleRules
{
	public HapticImporter(TargetInfo Target)
	{
		
		PCHUsage = PCHUsageMode.NoSharedPCHs;
		MinFilesUsingPrecompiledHeaderOverride = 0;




		PublicIncludePaths.AddRange(
			new string[] {
				//"HapticSuit/Public" //<-- added
			}
		);



		PrivateIncludePaths.AddRange(
			new string[] {
				"HapticImporter/Private" //<-- added
				
			}
		);

		PrivateDependencyModuleNames.AddRange(
		new string[] {
				"Core",
				"CoreUObject",
				"Json",
				"JsonUtilities",
				"Engine",
				"UnrealEd",
				"AssetTools",
				"ContentBrowser",
				"HapticSuit" //<-- added
		});

		PublicDependencyModuleNames.AddRange(
				new string[]
				{
					"HapticSuit" //<-- added
				}
		);

		PrivateIncludePathModuleNames.AddRange(
			new string[] {
				"AssetTools",
				"AssetRegistry"
			});

		DynamicallyLoadedModuleNames.AddRange(
			new string[] {
				"AssetRegistry"
			});
	
	}
}
