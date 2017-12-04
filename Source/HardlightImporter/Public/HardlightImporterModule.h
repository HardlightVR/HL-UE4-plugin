// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once


#include "Modules/ModuleManager.h"
#include "PlatformFilemanager.h"
#include "GenericPlatformFile.h"
#include "Runtime/Core/Public/Templates/UniquePtr.h"
#include "Runtime/Core/Public/Templates/SharedPointer.h"
class FHardlightImporterModule : public IModuleInterface
{
public:

	//DECLARE_LOG_CATEGORY_EXTERN(LogHapticPlugin, Log, All);
	/* IHapticEventDrivenDevice implementation */


	
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	FHardlightImporterModule();
	static inline FHardlightImporterModule& Get()
	{
		return FModuleManager::LoadModuleChecked<FHardlightImporterModule>("HardlightImporter");
	}
private:
	TSharedRef<IAssetTypeActions> m_assetActions;
	TSharedRef<IAssetTypeActions> m_sequenceActions;
	TSharedRef<IAssetTypeActions> m_experienceActions;

};