// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "HapticImporterPrivatePCH.h"
#include "UHapticAssetFactory.h"
#include "UHapticAsset.h"

UHapticAssetFactory::UHapticAssetFactory(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	bCreateNew = true;
	bEditAfterNew = true;
	SupportedClass = UHapticAsset::StaticClass();
}
UObject* UHapticAssetFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	return nullptr;
}
