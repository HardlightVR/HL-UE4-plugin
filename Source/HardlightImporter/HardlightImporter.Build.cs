// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.IO;
using System;

public class HardlightImporter : ModuleRules
{
	public HardlightImporter(ReadOnlyTargetRules Target) : base(Target)
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
				"HardlightImporter/Private" //<-- added
				
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
				"HardlightSDK" //<-- added
		});

		PublicDependencyModuleNames.AddRange(
				new string[]
				{
					"HardlightSDK" //<-- added
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
