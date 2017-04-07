// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once


#include "Modules/ModuleManager.h"
#include "NSLoader_fwds.h"
#include "PlatformFilemanager.h"
#include "GenericPlatformFile.h"
#include "Runtime/Core/Public/Templates/UniquePtr.h"
#include "IHapticEventDrivenDevice.h"

#include "ITimeline.h"

class FHapticSuitModule : public IModuleInterface, public IHapticEventDrivenDevice
{
public:

	//DECLARE_LOG_CATEGORY_EXTERN(LogHapticPlugin, Log, All);
	/* IHapticEventDrivenDevice implementation */


	TUniquePtr<ITimeline> CreateTimeline() override;

	bool GetServiceInfo(NSVR_ServiceInfo* infoPtr);
	bool GetDeviceInfo(NSVR_DeviceInfo* infoPtr);

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	bool PluginLoadedSuccessfully();

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

	NSVR_System* m_system;
};