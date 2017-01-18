// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "ModuleManager.h"
#include "NSLoader.h"

class FHapticSuitModule : public IModuleInterface
{
public:

	//DECLARE_LOG_CATEGORY_EXTERN(LogHapticPlugin, Log, All);

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
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

	NSVRPlugin Plugin;
};