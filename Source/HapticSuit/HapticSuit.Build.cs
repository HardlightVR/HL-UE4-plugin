// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.IO;
using System;

public class HapticSuit : ModuleRules
{

	private string ModulePath
	{
		get { return ModuleDirectory; }
	}

	private string ThirdPartyPath
	{
		get { return Path.GetFullPath(Path.Combine(ModulePath, "../../ThirdParty/")); }
	}

	private string BinariesPath
	{
		get { return Path.GetFullPath(Path.Combine(ModulePath, "../../Binaries/")); }
	}

	private string LibraryPath
	{
		get { return Path.GetFullPath(Path.Combine(ThirdPartyPath, "lib")); }
	}
	public HapticSuit(TargetInfo Target)
	{
		
		PCHUsage = PCHUsageMode.NoSharedPCHs;
        MinFilesUsingPrecompiledHeaderOverride = 0; // or other larger numbers
       
	
		PublicIncludePaths.AddRange(
			new string[] { "HapticSuit/Public" }
			);


		PrivateIncludePaths.AddRange(
			new string[] { "HapticSuit/Private", "ThirdParty/include" }
			);

		if (UEBuildConfiguration.bBuildEditor)
		{
			//PublicDependencyModuleNames.Add("HapticImporter");
		}

		PublicDependencyModuleNames.AddRange(
			new string[] { "Core", "CoreUObject", "Engine", "Projects"}
			);

		PrivateDependencyModuleNames.AddRange(
			new string[] { "Core", "CoreUObject", "Engine", "Projects" }
			);


		if (!LoadNullSpaceLib(Target))
		{
			Console.WriteLine("Platform not supported!");
		}
	}

	public bool LoadNullSpaceLib(TargetInfo Target)
	{
		bool isLibrarySupported = false;

		if ((Target.Platform == UnrealTargetPlatform.Win64) || (Target.Platform == UnrealTargetPlatform.Win32))
		{
			isLibrarySupported = true;

			string PlatformString = (Target.Platform == UnrealTargetPlatform.Win64) ? "Win64" : "Win32";

			PublicAdditionalLibraries.Add(Path.Combine(LibraryPath, PlatformString, "NSLoader.lib"));

			PublicDelayLoadDLLs.Add("NSLoader.dll");
			RuntimeDependencies.Add(new RuntimeDependency("$(EngineDir)/Binaries/ThirdParty/NullSpaceVR/" + Target.Platform.ToString() + "/" + "NSLoader.dll"));
		}
		else if (Target.Platform == UnrealTargetPlatform.Mac)
		{

			isLibrarySupported = false;


		}

		return isLibrarySupported;
	}

}
