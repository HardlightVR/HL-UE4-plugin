// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "HapticImporterPrivatePCH.h"
#include "FHapticTypeActions.h"

FText FHapticTypeActions::GetName() const
{
	return NSLOCTEXT("AssetTypeActions", "AssetTypeActions_HapticAsset", "Haptic Asset");
}

FColor FHapticTypeActions::GetTypeColor() const
{
	return FColor(149, 70, 255);
}

UClass* FHapticTypeActions::GetSupportedClass() const
{
	//TODO: IMPLEMENT
	return nullptr;
}

uint32 FHapticTypeActions::GetCategories() 
{
	return EAssetTypeCategories::Misc;
}

UThumbnailInfo * FHapticTypeActions::GetThumbnailInfo(UObject * Asset) const
{
	return nullptr;
}
