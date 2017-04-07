// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.IO;
using System;

public class HapticSuit : ModuleRules
{
	public HapticSuit(TargetInfo Target)
	{
		var HapticSuitPath = Path.GetFullPath(Path.Combine(ModuleDirectory, "../ThirdParty/"));

		//Go up two directories
		string BaseDirectory = Path.GetFullPath(Path.Combine(ModuleDirectory, "..", ".."));
		//string SuitPluginDirectory = Path.Combine(BaseDirectory, "ThirdParty", "", Target.Platform.ToString());
		string SuitPluginDirectory = Path.Combine(BaseDirectory, "ThirdParty", Target.Platform.ToString());

		var libPath = Path.Combine(HapticSuitPath, "lib");

		if (Directory.Exists(Path.Combine(BaseDirectory, "Plugins")))
		{
			Console.WriteLine("Plugins exists\n");
		}
		else
		{
			Console.WriteLine("Created Plugins Directory\n");
			Directory.CreateDirectory(Path.Combine(BaseDirectory, "Plugins"));
		}

		if (Directory.Exists(Path.Combine(ModuleDirectory, "Plugins")))
		{
			Console.WriteLine("Plugins exists\n");
		}
		else
		{
			Console.WriteLine("Created Plugins Directory\n");
			Directory.CreateDirectory(Path.Combine(ModuleDirectory, "Plugins"));
		}
		PCHUsage = PCHUsageMode.NoSharedPCHs;
        MinFilesUsingPrecompiledHeaderOverride = 0; // or other larger numbers
        //Target.bForceIncludePrecompiledHeader = true;
        // If this is set it seems to want to look in the Engine/Source folder. Specifying a file relative to this also doesn't seem to be sufficient.
        //SharedPCHHeaderFile = "";

       
		//
		//REFERENCE: Engine/.../nvanselsdk.Build.cs
		//	Reference piece for the DLL that's runtime with added dll stuff.
		
		switch (Target.Platform)
		{
			case UnrealTargetPlatform.Win64:
				PublicAdditionalLibraries.Add(Path.Combine(libPath, "Win64", "NSLoader.lib"));

				//Lines that didn't work:
				//PublicAdditionalLibraries.Add(Path.Combine(libPath, "x64", "NSLoader.dll"));
				//RuntimeDependencies.Add(new RuntimeDependency(Path.Combine(libPath, "x64", "NSLoader.dll")));
				break;

			case UnrealTargetPlatform.Win32:
				PublicAdditionalLibraries.Add(Path.Combine(libPath, "Win32", "NSLoader.lib"));

				//Lines that didn't work:
				//PublicAdditionalLibraries.Add(Path.Combine(libPath, "x86", "NSLoader.dll"));
				//RuntimeDependencies.Add(new RuntimeDependency(Path.Combine(libPath, "x86", "NSLoader.dll")));
				break;
		}

		//bool HaveDebugLib = File.Exists(BinariesPath + LibName + "d" + ".dll");

		//if (HaveDebugLib &&
		//	Target.Configuration == UnrealTargetConfiguration.Debug &&
		//	BuildConfiguration.bDebugBuildsActuallyUseDebugCRT)
		//{
		//	LibName += "d";
		//}

		//PublicAdditionalLibraries.Add(Path.Combine(LibraryPath, LibName + ".lib"));

		//string DLLName = LibName + ".dll";
		//PublicDelayLoadDLLs.Add(DLLName);
		//RuntimeDependencies.Add(new RuntimeDependency(BinariesPath + DLLName));

		//Definitions.Add("WITH_ANSEL=1");
		//Definitions.Add("ANSEL_DLL=" + DLLName);

		PublicIncludePaths.AddRange(
			new string[] { "HapticSuit/Public" }
			);


		PrivateIncludePaths.AddRange(
			new string[] { "HapticSuit/Private", "ThirdParty/include" }
			);


		PublicDependencyModuleNames.AddRange(
			new string[] { "Core", "CoreUObject", "Engine", "Projects" }
			);

		PrivateDependencyModuleNames.AddRange(
			new string[] { "Core", "CoreUObject", "Engine", "Projects" }
			);

		string PluginDirectory = Path.Combine(SuitPluginDirectory, "plugins");

		if (Directory.Exists(PluginDirectory))
		{
			foreach (string Plugin in Directory.EnumerateFiles(PluginDirectory))
			{
				RuntimeDependencies.Add(new RuntimeDependency(Plugin));
			}
		}
	}
}
