// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PlatformFilemanager.h"
#include "GenericPlatformFile.h"
#include "Runtime/Json/Public/Dom/JsonObject.h"
#include "UHapticAsset.h" //for UHapticAsset** and EAssetType
#include "FEffectStruct.h" //for EEffects


class UHapticSequence;
class UHapticPattern;
class UHapticExperience;

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


	int32 ParseArea(const FString& areaString);

	TMap<FString, EEffects> EffectsMap;
	TMap<FString, int32> AreasMap;
	void ParsePattern(UHapticPattern* NewPattern);
	void ParseExperience(UHapticExperience* NewExperience);
};