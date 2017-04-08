// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "HapticImporterPrivatePCH.h"
#include "HapticImporter.h"
#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "FHapticTypeActions.h"
#include "Runtime/Core/Public/Misc/Paths.h"
#include "Developer/AssetTools/Public/IAssetTools.h"
#include "UHapticAssetFactory.h"
#define LOCTEXT_NAMESPACE "FHapticImporterModule"
//DEFINE_LOG_CATEGORY(LogHapticPlugin);


void FHapticImporterModule::StartupModule()
{
	UE_LOG(LogTemp, Warning, TEXT("Startup Module for NSVR Importer Plugin"));
	
	IAssetTools& assetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();

	assetTools.RegisterAssetTypeActions(m_assetActions);

//	TSharedRef<UFactory> x = MakeShareable(new UHapticAssetFactory());
	

	
}

void FHapticImporterModule::ShutdownModule()
{
	UE_LOG(LogTemp, Warning, TEXT("Shutdown Module for NSVR Importer Plugin"));
	IAssetTools& assetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	assetTools.UnregisterAssetTypeActions(m_assetActions);
}

FHapticImporterModule::FHapticImporterModule(): m_assetActions(new FHapticTypeActions())
{
}





#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FHapticImporterModule, HapticImporter)