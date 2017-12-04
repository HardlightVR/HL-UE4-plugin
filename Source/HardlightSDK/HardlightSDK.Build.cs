// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.IO;
using System;

public class HardlightSDK : ModuleRules
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

	
	public HardlightSDK(ReadOnlyTargetRules Target) : base(Target)
	{

	

		PCHUsage = PCHUsageMode.NoSharedPCHs;
        MinFilesUsingPrecompiledHeaderOverride = 0; // or other larger numbers
       
	
		PublicIncludePaths.AddRange(
			new string[] { "HardlightSDK/Public"/*, Path.Combine(ThirdPartyPath, "NullSpaceVR", "include") */ }
			);


		
		PrivateIncludePaths.AddRange(
			new string[] { "HardlightSDK/Private", Path.Combine(ThirdPartyPath, "HardlightVR", "include")}
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


		if (!LoadHardlightLib(Target))
		{
			Console.WriteLine("Platform not supported!");
		}
	}

	public bool LoadHardlightLib(ReadOnlyTargetRules Target)
	{
		bool isLibrarySupported = false;

		if ((Target.Platform == UnrealTargetPlatform.Win64) || (Target.Platform == UnrealTargetPlatform.Win32))
		{
			isLibrarySupported = true;

			string PlatformString = (Target.Platform == UnrealTargetPlatform.Win64) ? "Win64" : "Win32";
			string LibrariesPath = Path.Combine(ThirdPartyPath, "HardlightVR", "lib");
			string fullLibPath = Path.Combine(LibrariesPath, PlatformString, "Hardlight.lib");
			PublicAdditionalLibraries.Add(fullLibPath);
			
		}
		else if (Target.Platform == UnrealTargetPlatform.Mac)
		{

			isLibrarySupported = false;


		}

		if (isLibrarySupported)
		{
			var incl = Path.Combine(ThirdPartyPath, "HardlightVR", "include");
			Console.WriteLine("Adding the include path: " + incl);
			PublicIncludePaths.Add(incl);
		}

		return isLibrarySupported;
	}

}
