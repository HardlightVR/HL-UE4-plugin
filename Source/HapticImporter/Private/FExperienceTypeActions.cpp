// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "HapticImporterPrivatePCH.h"
#include "FExperienceTypeActions.h"
#include "UHapticExperience.h"
FText FExperienceTypeActions::GetName() const
{
	return NSLOCTEXT("AssetTypeActions", "AssetTypeActions_HapticExperience", "Haptic Experience");
}

FColor FExperienceTypeActions::GetTypeColor() const
{
	return FColor(158, 1, 1);
}

UClass* FExperienceTypeActions::GetSupportedClass() const
{
	return UHapticExperience::StaticClass();
}

uint32 FExperienceTypeActions::GetCategories()
{
	return EAssetTypeCategories::Misc;
}

UThumbnailInfo * FExperienceTypeActions::GetThumbnailInfo(UObject * Asset) const
{
	return nullptr;
}
