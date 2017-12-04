// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "HapticSuitPrivatePCH.h"
#include "HapticSuit.h"
#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

#include "Runtime/Core/Public/Misc/Paths.h"


#include <string>
#include "FTimelineImpl.h"
#define LOCTEXT_NAMESPACE "FHapticSuitModule"


TUniquePtr<ITimeline> FHapticSuitModule::CreateTimeline()
{

	return TUniquePtr<ITimeline>(new FTimelineImpl(&m_system));
}

bool FHapticSuitModule::GetServiceInfo(HLVR_RuntimeInfo * infoPtr)
{
	if (auto info = m_system.get_runtime_info()) {
		if (infoPtr != nullptr) {
			*infoPtr = *info;
		}
		return true;
	}
	return false;
}


bool FHapticSuitModule::PauseAllHaptics()
{
	return (bool) m_system.suspend_all_haptics();
}

bool FHapticSuitModule::ResumeAllHaptics()
{
	return (bool) m_system.resume_all_haptics();

}

bool FHapticSuitModule::IsAtLeastOneDevicePresent()  {

	auto devices = m_system.get_known_devices();
	for (const auto& device : devices) {
		if (device.Status == HLVR_DeviceStatus::HLVR_DeviceStatus_Connected) {
			return true;
		}

	}

	return false;

}


bool FHapticSuitModule::ClearAllHaptics()
{
	return (bool) m_system.cancel_all_haptics();
}

void FHapticSuitModule::StartupModule()
{
	UE_LOG(LogTemp, Warning, TEXT("Startup Module for HLVR Plugin"));


	if (!HLVR_Version_IsCompatibleDLL()) {
		UE_LOG(LogTemp, Warning, TEXT("Will not initialize HLVR library, DLL is not compatible with headers"));

		return;
	}
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	auto result = hlvr::system::make();
	if (result) {
		m_system = *std::move(result);
		check(m_system);
		UE_LOG(LogTemp, Warning, TEXT("HLVR System created successfully"));

	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Failed to instantiate HLVR System"));

	}
	

	
}

void FHapticSuitModule::ShutdownModule()
{
	UE_LOG(LogTemp, Warning, TEXT("Shutdown Module for HLVR Plugin"));
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	m_system.shutdown();
}


bool FHapticSuitModule::PluginLoadedSuccessfully()
{
	return (bool) m_system;
}





#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FHapticSuitModule, HardlightSDK)