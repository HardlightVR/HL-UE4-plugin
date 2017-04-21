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

	inline bool GetServiceInfo(NSVR_ServiceInfo* infoPtr);
	inline bool GetDeviceInfo(NSVR_DeviceInfo* infoPtr);
	inline bool PauseAllHaptics();
	inline bool ResumeAllHaptics();
	inline bool ClearAllHaptics();
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	inline bool PluginLoadedSuccessfully();


	static inline FHapticSuitModule& Get()
	{
		return FModuleManager::LoadModuleChecked<FHapticSuitModule>("HapticSuit");
	}

	

	NSVR_System* m_system;
};