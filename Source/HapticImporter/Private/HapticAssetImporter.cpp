// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "HapticImporterPrivatePCH.h"
#include "HapticAssetImporter.h"
#include "UHapticAsset.h"
#include "UHapticAssetFactory.h"
#include "UHapticSequence.h"
#include "UHapticPattern.h"
#include "UHapticExperience.h"
#include "IAssetTools.h"
#include "AssetToolsModule.h"
#include "Editor/UnrealEd/Public/ObjectTools.h"
#include "AssetRegistryModule.h"
#include "Json.h"



TSharedPtr<class FJsonObject> ReadObject(TSharedPtr<class FJsonObject> Item, const FString& Key)
{
	if (Item->HasTypedField<EJson::Object>(Key))
	{
		return Item->GetObjectField(Key);
	}
	else
	{
		return nullptr;
	}
}

TSharedPtr<FJsonObject> ParseJSON(const FString& FileContents, const FString& NameForErrors)
{
	// Load the file up (JSON format)
	if (!FileContents.IsEmpty())
	{
		const TSharedRef< TJsonReader<> >& Reader = TJsonReaderFactory<>::Create(FileContents);

		TSharedPtr<FJsonObject> HapticDescriptionObject;
		if (FJsonSerializer::Deserialize(Reader, HapticDescriptionObject) && HapticDescriptionObject.IsValid())
		{
			// File was loaded and deserialized OK!
			return HapticDescriptionObject;
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Failed to parse the hdf '%s' : '%s'"), *NameForErrors, *Reader->GetErrorMessage());
			return nullptr;
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("HDF '%s' was empty. Cannot import."), *NameForErrors);
		return nullptr;
	}
}


FHapticAssetImporter::FHapticAssetImporter()
{

}

bool ParseMetaBlock(TSharedPtr<FJsonObject>& HapticDescriptorObject, const FString& NameForErrors)
{
	auto root_effect = ReadObject(HapticDescriptorObject, "root_effect");
	if (!root_effect.IsValid()) {
		return false;
	}

	auto effect_type = root_effect->GetStringField("type");
	if (!(effect_type == "sequence" || effect_type =="pattern" || effect_type == "experience")) {
		return false;
	}
	//add check for the effect name, and other keys?
	return true;
}


bool FHapticAssetImporter::CanImportJSON(const FString& FileContents)
{
	TSharedPtr<FJsonObject> HapticDescriptorObject = ParseJSON(FileContents, FString());
	if (HapticDescriptorObject.IsValid())
	{
		FString Unused;
		return ParseMetaBlock(HapticDescriptorObject, FString());
	}

	return false;
}


bool FHapticAssetImporter::Import(TSharedPtr<FJsonObject> HapticDescriptorObject, const FString& NameForErrors)
{
	bool bLoadedSuccessfully = ParseMetaBlock(HapticDescriptorObject, NameForErrors);
	if (bLoadedSuccessfully)
	{
		FString assetStr = HapticDescriptorObject->GetObjectField("root_effect")->GetStringField("type");
		if (assetStr == "sequence") {
			AssetType = UHapticAsset::EAssetType::Sequence;
		}
		else if (assetStr == "pattern") {
			AssetType = UHapticAsset::EAssetType::Pattern;
		}
		else if (assetStr == "experience") {
			AssetType = UHapticAsset::EAssetType::Experience;
		}

		RootKey = HapticDescriptorObject->GetObjectField("root_effect")->GetStringField("name");
		RawData = *HapticDescriptorObject;
	}
	return bLoadedSuccessfully;
}

bool FHapticAssetImporter::ImportSequence(UHapticAsset** HapticAsset)
{
	*HapticAsset = *ImportedSequences.Find(RootKey);
	return true;
}

bool FHapticAssetImporter::ImportPattern(UHapticAsset** HapticAsset)
{
	*HapticAsset = *ImportedPatterns.Find(RootKey);
	return true;
}

bool FHapticAssetImporter::ImportExperience(UHapticAsset** HapticAsset)
{
	*HapticAsset = *ImportedExperiences.Find(RootKey);
	return true;
}

bool FHapticAssetImporter::ImportFromString(const FString& FileContents, const FString& NameForErrors)
{
	TSharedPtr<FJsonObject> HapticDescriptorObject = ParseJSON(FileContents, NameForErrors);
	return HapticDescriptorObject.IsValid() && Import(HapticDescriptorObject, NameForErrors);
}

UHapticSequence* CreateNewSequence(FString key, UObject* InParent, EObjectFlags Flags) {
	const FString SanitizeName = ObjectTools::SanitizeObjectName(key);
	UHapticSequence* Result = NewObject<UHapticSequence>(InParent, FName(*SanitizeName), Flags);
	Result->AssetType = UHapticAsset::EAssetType::Sequence;
	return Result;
}

UHapticPattern* CreateNewPattern(FString key, UObject* InParent, EObjectFlags Flags) {
	const FString SanitizeName = ObjectTools::SanitizeObjectName(key);
	UHapticPattern* Result = NewObject<UHapticPattern>(InParent, FName(*SanitizeName), Flags);
	Result->AssetType = UHapticAsset::EAssetType::Pattern;
	return Result;
}
UHapticExperience* CreateNewExperience(FString key, UObject* InParent, EObjectFlags Flags) {
	const FString SanitizeName = ObjectTools::SanitizeObjectName(key);
	UHapticExperience* Result = NewObject<UHapticExperience>(InParent, FName(*SanitizeName), Flags);
	Result->AssetType = UHapticAsset::EAssetType::Experience;
	return Result;
}
bool FHapticAssetImporter::PerformImport(UObject* InParent, FName Name, EObjectFlags Flags, UHapticAsset** HapticAsset)
{
	//Todo: Just refactor this. Import everything in the HDF, because it's needed: it's in the HDF.

	//pseudocode:
	/*
	
	foreach (sequence in sequence_definitions) {
		if (!Imported(sequence)){
			Create(sequence)
		}
	}

	foreach (pattern in pattern_definitions) {
		if (!Imported(pattern)){
			Create(pattern)
		}
	}

	foreach (experience in experience_definitions) {
		if (!Imported(experience)){
			Create(experience)
		}
	}

	switch (experienceType) {
	case Sequence:
		return ImportSequence(HapticAsset);
	case Pattern:
		return ImportPattern(HapticAsset);
	case Experience:
		return ImportExperience(HapticAsset);
	default:
		return false;
	}
	*/


	const auto& SequenceDefinitions = RawData.GetObjectField("sequence_definitions");
	const auto& PatternDefinitions = RawData.GetObjectField("pattern_definitions");
	const auto& ExperienceDefinitions = RawData.GetObjectField("experience_definitions");
	for (const auto& sequence : SequenceDefinitions->Values) {
		if (!ImportedSequences.Contains(sequence.Key)) {
			UHapticSequence* NewSequence = CreateNewSequence(sequence.Key, InParent, Flags);
			NewSequence->RawData = RawData;
			NewSequence->PopulateDataFromJson();
			NewSequence->EffectName = sequence.Key;
			ImportedSequences.Add(sequence.Key, NewSequence);
		}
	}

	for (const auto& pattern : PatternDefinitions->Values) {
		if (!ImportedPatterns.Contains(pattern.Key)) {
			UHapticPattern* NewPattern = CreateNewPattern(pattern.Key, InParent, Flags);
			NewPattern->RawData = RawData;
			NewPattern->PopulateDataFromJson();
			NewPattern->EffectName = pattern.Key;
			ImportedPatterns.Add(pattern.Key, NewPattern);
		}
	}

	for (const auto& experience : ExperienceDefinitions->Values) {
		if (!ImportedExperiences.Contains(experience.Key)) {
			UHapticExperience* NewExperience = CreateNewExperience(experience.Key, InParent, Flags);
			NewExperience->RawData = RawData;
			NewExperience->PopulateDataFromJson();

			NewExperience->EffectName = experience.Key;
			ImportedExperiences.Add(experience.Key, NewExperience);
		}
	}

	switch (AssetType) {
	case UHapticAsset::EAssetType::Sequence:
		return ImportSequence(HapticAsset);
	case UHapticAsset::EAssetType::Pattern:
		return ImportPattern(HapticAsset);
	case UHapticAsset::EAssetType::Experience:
		return ImportExperience(HapticAsset);
	default:
		return false;
	}


	//FAssetToolsModule& AssetToolsModule = FModuleManager::GetModuleChecked<FAssetToolsModule>("AssetTools");

	//if (AssetType == UHapticAsset::EAssetType::Sequence) {
	//	const FString SanitizedSequenceName = ObjectTools::SanitizeObjectName(RootKey);

	//	*HapticAsset = NewObject<UHapticSequence>(InParent, FName(*SanitizedSequenceName), Flags);
	//	(*HapticAsset)->AssetType = AssetType;
	//	(*HapticAsset)->RawData = RawData;
	//	(*HapticAsset)->EffectName = RootKey;
	//	return true;
	//}
	//else if (AssetType == UHapticAsset::EAssetType::Pattern) {

	//	const FString SanitizedPatternName = ObjectTools::SanitizeObjectName(RootKey);

	//	auto patternParent = NewObject<UHapticPattern>(InParent,FName(*SanitizedPatternName), Flags);
	//	patternParent->AssetType = UHapticAsset::EAssetType::Pattern;
	//	patternParent->RawData = RawData;
	//	patternParent->EffectName = RootKey;
	//
	//	auto pattern_defs = RawData.GetObjectField("pattern_definitions")->GetArrayField(RootKey);
	//	for (const auto& seq : pattern_defs) {
	//		FString sequence_name = seq->AsObject()->GetStringField("sequence");
	//		if (ImportedSequences.Contains(sequence_name)) {
	//			patternParent->SequenceArray.Add(TAssetPtr<UHapticSequence>(*ImportedSequences.Find(sequence_name)));
	//			
	//		}
	//		else {
	//			const FString SanitizedSequenceName = ObjectTools::SanitizeObjectName(sequence_name);

	//			auto newSeq = NewObject<UHapticSequence>(InParent, FName(*SanitizedSequenceName), Flags);
	//			FAssetRegistryModule::AssetCreated(newSeq);

	//			newSeq->Modify();

	//			newSeq->AssetType = UHapticAsset::EAssetType::Sequence;
	//			newSeq->RawData = RawData;
	//			newSeq->EffectName = sequence_name;
	//			newSeq->PopulateDataFromJson();
	//			patternParent->SequenceArray.Add(TAssetPtr<UHapticSequence>(newSeq));
	//			ImportedSequences.Add(sequence_name, newSeq);
	//			newSeq->PostEditChange();
	//		
	//		}
	//		
	//	}
	//	*HapticAsset = patternParent;
	//	return true;
	//	
	//}
	//else if (AssetType == UHapticAsset::EAssetType::Experience) {
	//	const FString SanitizedExperienceName = ObjectTools::SanitizeObjectName(RootKey);

	//	auto experienceParent = NewObject<UHapticExperience>(InParent, FName(*SanitizedExperienceName), Flags);
	//	experienceParent->AssetType = UHapticAsset::EAssetType::Experience;
	//	experienceParent->RawData = RawData;
	//	experienceParent->EffectName = RootKey;

	//	auto experience_defs = RawData.GetObjectField("experience_definitions")->GetArrayField(RootKey);
	//	for (const auto& seq :experience_defs) {
	//		FString pattern_name = seq->AsObject()->GetStringField("pattern");
	//		if (ImportedPatterns.Contains(pattern_name)) {
	//			experienceParent->PatternArray.Add(TAssetPtr<UHapticPattern>(*ImportedPatterns.Find(pattern_name)));

	//		}
	//		else {
	//			
	//			const FString SanitizedPatternName = ObjectTools::SanitizeObjectName(pattern_name);

	//			auto newPat = NewObject<UHapticPattern>(InParent, FName(*SanitizedPatternName), Flags);
	//			FAssetRegistryModule::AssetCreated(newPat);

	//			newPat->Modify();

	//			newPat->AssetType = UHapticAsset::EAssetType::Sequence;
	//			newPat->RawData = RawData;
	//			newPat->EffectName =pattern_name;
	//			newPat->PopulateDataFromJson();
	//			experienceParent->PatternArray.Add(TAssetPtr<UHapticPattern>(newPat));
	//			ImportedPatterns.Add(pattern_name, newPat);
	//			newPat->PostEditChange();

	//		}

	//	}
	//	*HapticAsset = experienceParent;
	//	return true;
	//}

	//return false;
}
