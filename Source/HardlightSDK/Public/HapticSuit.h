// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once


#include "Modules/ModuleManager.h"
#include "PlatformFilemanager.h"
#include "GenericPlatformFile.h"
#include "Runtime/Core/Public/Templates/UniquePtr.h"
#include "IHapticEventDrivenDevice.h"

#include "ITimeline.h"

#include "bindings/cpp/hlvr_system.hpp"

class FHapticSuitModule : public IModuleInterface, public IHapticEventDrivenDevice
{
public:

	//DECLARE_LOG_CATEGORY_EXTERN(LogHapticPlugin, Log, All);
	/* IHapticEventDrivenDevice implementation */


	TUniquePtr<ITimeline> CreateTimeline() override;

	inline bool GetServiceInfo(HLVR_RuntimeInfo* infoPtr);
	inline bool PauseAllHaptics();
	inline bool ResumeAllHaptics();
	inline bool ClearAllHaptics();
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	inline bool PluginLoadedSuccessfully();


	inline bool IsAtLeastOneDevicePresent();

	static inline FHapticSuitModule& Get()
	{
		return FModuleManager::LoadModuleChecked<FHapticSuitModule>("HardlightSDK");
	}

	

	hlvr::system m_system;
};