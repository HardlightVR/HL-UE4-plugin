// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "HapticImporterPrivatePCH.h"
#include "HapticImporterModule.h"
#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "Runtime/Core/Public/Misc/Paths.h"
#include "Developer/AssetTools/Public/IAssetTools.h"
#include "FPatternTypeActions.h"
#include "FSequenceTypeActions.h"
#include "FExperienceTypeActions.h"
#include "Editor/UnrealEd/Public/ObjectTools.h"
#define LOCTEXT_NAMESPACE "FHapticImporterModule"

//DEFINE_LOG_CATEGORY(LogHapticPlugin);


void FHapticImporterModule::StartupModule()
{
	UE_LOG(LogTemp, Warning, TEXT("Startup Module for NSVR Importer Plugin"));
	
	IAssetTools& assetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();

	assetTools.RegisterAssetTypeActions(m_assetActions);
	assetTools.RegisterAssetTypeActions(m_sequenceActions);
	assetTools.RegisterAssetTypeActions(m_experienceActions);

	
}

void FHapticImporterModule::ShutdownModule()
{
	UE_LOG(LogTemp, Warning, TEXT("Shutdown Module for NSVR Importer Plugin"));
	IAssetTools& assetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	assetTools.UnregisterAssetTypeActions(m_assetActions);
	assetTools.UnregisterAssetTypeActions(m_sequenceActions);
}

FHapticImporterModule::FHapticImporterModule(): 
	m_assetActions(new FPatternTypeActions())
  , m_sequenceActions(new FSequenceTypeActions())
  , m_experienceActions(new FExperienceTypeActions())
{
}





#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FHapticImporterModule, HapticImporter)