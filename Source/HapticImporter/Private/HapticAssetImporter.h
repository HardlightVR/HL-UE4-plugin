// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once


#include "PlatformFilemanager.h"
#include "GenericPlatformFile.h"
#include "UHapticAsset.h"
#include "FEffectStruct.h"
#include "Runtime/Json/Public/Dom/JsonObject.h"

class UHapticSequence;
class UHapticPattern;
class UHapticExperience;
class UHapticAssetFactory;
class FHapticAssetImporter
{
public:
	FHapticAssetImporter();

	static bool CanImportJSON(const FString& FileContents);
	bool ImportFromString(const FString& FileContents, const FString& NameForErrors);
	bool PerformImport(UObject* InParent, FName Name, EObjectFlags Flags, UHapticAsset** HapticAsset);
private:
	bool Import(TSharedPtr<FJsonObject> HapticDescriptorObject, const FString& NameForErrors);
	bool ParseSequence(UHapticSequence* sequence);
	UHapticAsset::EAssetType AssetType;
	FString RootKey;
	FJsonObject RawData;

	TMap<FString, UHapticSequence*> ImportedSequences;
	TMap<FString, UHapticPattern*> ImportedPatterns;
	TMap<FString, UHapticExperience*> ImportedExperiences;

	bool ImportSequence(UHapticAsset** HapticAsset);
	bool ImportPattern(UHapticAsset** HapticAsset);
	bool ImportExperience(UHapticAsset** HapticAsset);
	int32 ParseArea(const FString& areaString);

	TMap<FString, EEffects> EffectsMap;
	TMap<FString, int32> AreasMap;
};