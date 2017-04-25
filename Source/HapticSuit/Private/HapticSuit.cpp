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

bool FHapticSuitModule::PauseAllHaptics()
{
	return NSVR_SUCCESS(NSVR_System_Haptics_Pause(m_system));
}

bool FHapticSuitModule::ResumeAllHaptics()
{
	return NSVR_SUCCESS(NSVR_System_Haptics_Resume(m_system));

}

bool FHapticSuitModule::ClearAllHaptics()
{
	return NSVR_SUCCESS(NSVR_System_Haptics_Destroy(m_system));
}

void FHapticSuitModule::StartupModule()
{
	UE_LOG(LogTemp, Warning, TEXT("Startup Module for NSVR Plugin"));


	if (!NSVR_Version_IsCompatibleDLL()) {
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





#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FHapticSuitModule, HapticSuit)