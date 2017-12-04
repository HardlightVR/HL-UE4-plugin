// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "HardlightImporterPrivatePCH.h"
#include "FPatternTypeActions.h"
#include "UHapticPattern.h"
FText FPatternTypeActions::GetName() const
{
	return NSLOCTEXT("AssetTypeActions", "AssetTypeActions_HapticPattern", "Haptic Pattern");
}

FColor FPatternTypeActions::GetTypeColor() const
{
	return FColor(38, 89, 106);
}

UClass* FPatternTypeActions::GetSupportedClass() const
{
	return UHapticPattern::StaticClass();
}

uint32 FPatternTypeActions::GetCategories()
{
	return EAssetTypeCategories::Misc;
}

