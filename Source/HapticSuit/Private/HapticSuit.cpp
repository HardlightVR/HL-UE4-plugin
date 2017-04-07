// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "HapticSuitPrivatePCH.h"
#include "HapticSuit.h"
#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

#include "Runtime/Core/Public/Misc/Paths.h"


#include "nsloader.h"
//#include "FTimelineImpl.h"
#include <string>
#include "FTimelineImpl.h"
#define LOCTEXT_NAMESPACE "FHapticSuitModule"
//DEFINE_LOG_CATEGORY(LogHapticPlugin);


TUniquePtr<ITimeline> FHapticSuitModule::CreateTimeline()
{

	return TUniquePtr<ITimeline>(new FTimelineImpl(m_system));
}

bool FHapticSuitModule::GetServiceInfo(NSVR_ServiceInfo * infoPtr)
{
	return NSVR_SUCCESS(NSVR_System_GetServiceInfo(m_system, infoPtr));
}

bool FHapticSuitModule::GetDeviceInfo(NSVR_DeviceInfo * infoPtr)
{
	return NSVR_SUCCESS(NSVR_System_GetDeviceInfo(m_system, infoPtr));
}

void FHapticSuitModule::StartupModule()
{
	UE_LOG(LogTemp, Warning, TEXT("Startup Module for NSVR Plugin"));

	if (!NSVR_IsCompatibleDLL()) {
		UE_LOG(LogTemp, Warning, TEXT("Will not initialize NSVR library, DLL is not compatible with headers"));

		return;
	}
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	NSVR_Result result = NSVR_System_Create(&m_system);
	if (NSVR_FAILURE(result)) {
		UE_LOG(LogTemp, Warning, TEXT("Failed to load the NSVR library"));
	}
	else {
		check(m_system != nullptr && "System is nullptr after creating!");
	}

	
}

void FHapticSuitModule::ShutdownModule()
{
	UE_LOG(LogTemp, Warning, TEXT("Shutdown Module for NSVR Plugin"));
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	NSVR_System_Release(&m_system);
	check(m_system == nullptr && "System isn't nullptr after releasing!");
}


bool FHapticSuitModule::PluginLoadedSuccessfully()
{
	return (m_system != nullptr);
}



bool FHapticSuitModule::LoadAndPlaySequenceOnAll(FString SequenceName)
{
	return true;
	//return LoadAndPlaySequence(SequenceName, (int32)AreaFlag::All_Areas);
}

bool FHapticSuitModule::LoadAndPlaySequence(FString SequenceName, int32 Where)
{
	//bool loadedSuccessfully = NSVR_Load(Plugin, TCHAR_TO_ANSI(*SequenceName), FileType::Sequence);

	////ensureMsgf(loadedSuccessfully, TEXT("Sequence [%s] loaded unsuccessfully: Check namespace, file name & JSON file contents"), SequenceName);
	//if (!loadedSuccessfully)
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("Sequence loaded unsuccessfully: Check namespace, file name & JSON file contents"));
	//	return false;
	//}
	////Generate a unique handle for use with this sequence
	//unsigned int handle = NSVR_GenHandle(Plugin);
	////Communicate with the service to actually create the effect with the given handle
	//bool createdSuccessfully = NSVR_CreateSequence(Plugin, handle, TCHAR_TO_ANSI(*SequenceName), (AreaFlag)Where);

	////ensureMsgf(createdSuccessfully, TEXT("Sequence [%s] was loaded successfully but failed to create handle. Contact NullSpace VR's Software Team."), SequenceName);
	//if (!createdSuccessfully)
	//	return false;

	//NSVR_HandleCommand(Plugin, handle, Command::PLAY);
	return true;
}

bool FHapticSuitModule::LoadAndPlayExperience(FString ExperienceName)
{
	//bool loadedSuccessfully = NSVR_Load(Plugin, TCHAR_TO_ANSI(*ExperienceName), FileType::Experience);

	//if (!loadedSuccessfully)
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("Experience loaded unsuccessfully: Check namespace, file name & JSON file contents"));
	//	return false;
	//}

	////Generate a unique handle for use with this sequence
	//unsigned int handle = NSVR_GenHandle(Plugin);
	////Communicate with the service to actually create the effect with the given handle
	//bool createdSuccessfully = NSVR_CreateExperience(Plugin, handle, TCHAR_TO_ANSI(*ExperienceName));
	////ensureMsgf(createdSuccessfully, TEXT("Sequence [%s] was loaded successfully but failed to create handle. Contact NullSpace VR's Software Team."), ExperienceName);
	//if (!createdSuccessfully)
	//	return false;

	////Now play the effect!
	//NSVR_HandleCommand(Plugin, handle, Command::PLAY);
	return true;
}

bool FHapticSuitModule::LoadAndPlayPattern(FString PatternName)
{
	//bool loadedSuccessfully = NSVR_Load(Plugin, TCHAR_TO_ANSI(*PatternName), FileType::Pattern);

	////UE_LOG(LogHapticPlugin, Log, TEXT(“Pattern [%s] loaded unsuccessfully: Check namespace, file & JSON file contents”), *PatternName);

	//if (!loadedSuccessfully)
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("Pattern loaded unsuccessfully: Check namespace, file name & JSON file contents"));
	//	return false;
	//}

	////Generate a unique handle for use with this sequence
	//unsigned int handle = NSVR_GenHandle(Plugin);
	////Communicate with the service to actually create the effect with the given handle
	//bool createdSuccessfully = NSVR_CreatePattern(Plugin, handle, TCHAR_TO_ANSI(*PatternName));

	////ensureMsgf(createdSuccessfully, TEXT("Sequence [%s] was loaded successfully but failed to create handle. Contact NullSpace VR's Software Team."), PatternName);
	//if (!createdSuccessfully)
	//	return false;

	////Now play the effect!
	//NSVR_HandleCommand(Plugin, handle, Command::PLAY);
	return true;
}

void FHapticSuitModule::ClearAllHaptics()
{
	/*NSVR_EngineCommand(Plugin, EngineCommand::CLEAR_ALL);*/
}



#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FHapticSuitModule, HapticSuit)