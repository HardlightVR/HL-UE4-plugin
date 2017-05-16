// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "HapticImporterPrivatePCH.h"
#include "UHapticSequenceFactory.h"
#include "UHapticAsset.h"
#include "Runtime/Core/Public/GenericPlatform/GenericPlatformFile.h"
#include "Runtime/Core/Public/Misc/FileHelper.h"
#include "Editor/UnrealEd/Public/Editor.h"
#include "Runtime/Core/Public/GenericPlatform/GenericPlatformProcess.h"
#include "UHapticSequence.h"

UHapticSequenceFactory::UHapticSequenceFactory(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	bEditAfterNew = true;
	bText = true;
	SupportedClass = UHapticSequence::StaticClass();
	
	bEditorImport = false;
	bCreateNew = true;


}


UObject* UHapticSequenceFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{

	auto effect = NewObject<UHapticAsset>(InParent, UHapticSequence::StaticClass(), Name, Flags);
	effect->EffectName = Name.ToString();
	effect->AssetType = UHapticAsset::EAssetType::Sequence;
	return effect;

}


