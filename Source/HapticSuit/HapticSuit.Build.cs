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

	
	public HapticSuit(ReadOnlyTargetRules Target) : base(Target)
	{

	

		PCHUsage = PCHUsageMode.NoSharedPCHs;
        MinFilesUsingPrecompiledHeaderOverride = 0; // or other larger numbers
       
	
		PublicIncludePaths.AddRange(
			new string[] { "HapticSuit/Public"/*, Path.Combine(ThirdPartyPath, "NullSpaceVR", "include") */ }
			);


		
		PrivateIncludePaths.AddRange(
			new string[] { "HapticSuit/Private", Path.Combine(ThirdPartyPath, "NullSpaceVR", "include")}
			);



	//	string NvCameraSDKIncPath = ThirdPartyPath +  "/include/";
		//PublicSystemIncludePaths.Add(NvCameraSDKIncPath);
		//PublicLibraryPaths.Add(Path.Combine(ThirdPartyPath, "NullSpaceVR", "lib"));
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

	public bool LoadNullSpaceLib(ReadOnlyTargetRules Target)
	{
		bool isLibrarySupported = false;

		if ((Target.Platform == UnrealTargetPlatform.Win64) || (Target.Platform == UnrealTargetPlatform.Win32))
		{
			isLibrarySupported = true;

			string PlatformString = (Target.Platform == UnrealTargetPlatform.Win64) ? "Win64" : "Win32";
			string LibrariesPath = Path.Combine(ThirdPartyPath, "NullSpaceVR", "lib");
			string fullLibPath = Path.Combine(LibrariesPath, PlatformString, "NSLoader.lib");
			PublicAdditionalLibraries.Add(fullLibPath);
			
		}
		else if (Target.Platform == UnrealTargetPlatform.Mac)
		{

			isLibrarySupported = false;


		}

		if (isLibrarySupported)
		{
			var incl = Path.Combine(ThirdPartyPath, "NullSpaceVR", "include");
			Console.WriteLine("Adding the include path: " + incl);
			PublicIncludePaths.Add(incl);
		}

		return isLibrarySupported;
	}

}
