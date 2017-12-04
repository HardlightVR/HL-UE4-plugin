// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "HardlightImporterPrivatePCH.h"
#include "HardlightImporterModule.h"
#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "Runtime/Core/Public/Misc/Paths.h"
#include "Developer/AssetTools/Public/IAssetTools.h"
#include "FPatternTypeActions.h"
#include "FSequenceTypeActions.h"
#include "FExperienceTypeActions.h"
#include "Editor/UnrealEd/Public/ObjectTools.h"
#define LOCTEXT_NAMESPACE "FHardlightImporterModule"

//DEFINE_LOG_CATEGORY(LogHapticPlugin);


void FHardlightImporterModule::StartupModule()
{
	UE_LOG(LogTemp, Warning, TEXT("Startup Module for HLVR Importer module"));
	
	IAssetTools& assetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();

	assetTools.RegisterAssetTypeActions(m_assetActions);
	assetTools.RegisterAssetTypeActions(m_sequenceActions);
	assetTools.RegisterAssetTypeActions(m_experienceActions);

	
}

void FHardlightImporterModule::ShutdownModule()
{
	UE_LOG(LogTemp, Warning, TEXT("Shutdown Module for HLVR Importer module"));
	IAssetTools& assetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	assetTools.UnregisterAssetTypeActions(m_assetActions);
	assetTools.UnregisterAssetTypeActions(m_sequenceActions);
}

FHardlightImporterModule::FHardlightImporterModule():
	m_assetActions(new FPatternTypeActions())
  , m_sequenceActions(new FSequenceTypeActions())
  , m_experienceActions(new FExperienceTypeActions())
{
}





#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FHardlightImporterModule, HardlightImporter)