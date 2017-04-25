// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once

//#include "HapticSuitPrivatePCH.h"

#include "Modules/ModuleManager.h"
#include "NSLoader.h"
#include "PlatformFilemanager.h"
#include "GenericPlatformFile.h"

class FHapticSuitModule : public IModuleInterface
{
public:

	//DECLARE_LOG_CATEGORY_EXTERN(LogHapticPlugin, Log, All);
	
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	void InitializeIfValidHapticDirectory();
	bool PluginLoadedSuccessfully();

	void ResetPlugin();
	bool LoadAndPlaySequenceOnAll(FString SequenceName);
	bool LoadAndPlaySequence(FString SequenceName, int32 Where);
	bool LoadAndPlayExperience(FString ExperienceName);
	bool LoadAndPlayPattern(FString PatternName);
	void ClearAllHaptics();

	static inline FHapticSuitModule& Get()
	{
		return FModuleManager::LoadModuleChecked<FHapticSuitModule>("HapticSuit");
	}

	//This function was provided by Rama and Zyr
	//https://wiki.unrealengine.com/File_Management,_Create_Folders,_Delete_Files,_and_More
	//#included "PlatformFilemanager.h" & "GenericPlatformFile.h" as well as commented out the const (unsure why it was there)
	//If this function cannot find or create the directory, returns false.			
	static FORCEINLINE bool VerifyOrCreateDirectory(const FString& TestDir) //const //The presence of this const is baffling.
	{
		// Every function call, unless the function is inline, adds a small
		// overhead which we can avoid by creating a local variable like so.
		// But beware of making every function inline!
		IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();

		// Directory Exists?
		if (!PlatformFile.DirectoryExists(*TestDir))
		{
			PlatformFile.CreateDirectory(*TestDir);

			if (!PlatformFile.DirectoryExists(*TestDir))
			{
				return false;
				//~~~~~~~~~~~~~~
			}
		}
		return true;
	}

	NSVRPlugin Plugin;
};