// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "HardlightImporterPrivatePCH.h"
#include "FSequenceTypeActions.h"
#include "UHapticSequence.h"
FText FSequenceTypeActions::GetName() const
{
	return NSLOCTEXT("AssetTypeActions", "AssetTypeActions_HapticSequence", "Haptic Sequence");
}

FColor FSequenceTypeActions::GetTypeColor() const
{
	return FColor(170, 168, 57);
	//exp: 38, 89, 106
}

UClass* FSequenceTypeActions::GetSupportedClass() const
{
	return UHapticSequence::StaticClass();
	
}

uint32 FSequenceTypeActions::GetCategories()
{
	return EAssetTypeCategories::Misc;
}

