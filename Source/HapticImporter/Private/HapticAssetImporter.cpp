// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "HapticImporterPrivatePCH.h"
#include "HapticAssetImporter.h"
#include "UHapticAsset.h"
#include "UHapticAssetFactory.h"
#include "UHapticSequence.h"
#include "UHapticPattern.h"
#include "IAssetTools.h"
#include "AssetToolsModule.h"
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
bool FHapticAssetImporter::ImportFromString(const FString& FileContents, const FString& NameForErrors)
{
	TSharedPtr<FJsonObject> HapticDescriptorObject = ParseJSON(FileContents, NameForErrors);
	return HapticDescriptorObject.IsValid() && Import(HapticDescriptorObject, NameForErrors);
}

bool FHapticAssetImporter::PerformImport(UObject* InParent, FName Name, EObjectFlags Flags, UHapticAsset** HapticAsset)
{
	FAssetToolsModule& AssetToolsModule = FModuleManager::GetModuleChecked<FAssetToolsModule>("AssetTools");

	if (AssetType == UHapticAsset::EAssetType::Sequence) {
		*HapticAsset = NewObject<UHapticSequence>(InParent, Name, Flags);
		(*HapticAsset)->AssetType = AssetType;
		(*HapticAsset)->RawData = RawData;
		(*HapticAsset)->EffectName = RootKey;
		return true;
	}
	else if (AssetType == UHapticAsset::EAssetType::Pattern) {
		auto patternParent = NewObject<UHapticPattern>(InParent, Name, Flags);
		patternParent->AssetType = UHapticAsset::EAssetType::Pattern;
		patternParent->RawData = RawData;
		patternParent->EffectName = RootKey;
	
		auto pattern_defs = RawData.GetObjectField("pattern_definitions")->GetArrayField(RootKey);
		for (const auto& seq : pattern_defs) {
			FString sequence_name = seq->AsObject()->GetStringField("sequence");
			if (ImportedSequences.Contains(sequence_name)) {
				patternParent->SequenceArray.Add(TAssetPtr<UHapticSequence>(*ImportedSequences.Find(sequence_name)));

			}
			else {
				FString AssetName;
				FString PackageName;
				auto newSeq = NewObject<UHapticSequence>(InParent, FName("aadsad"), Flags);
				FAssetRegistryModule::AssetCreated(newSeq);

				newSeq->Modify();

				newSeq->AssetType = UHapticAsset::EAssetType::Sequence;
				newSeq->RawData = RawData;
				newSeq->EffectName = sequence_name;
				newSeq->PopulateDataFromJson();
				patternParent->SequenceArray.Add(TAssetPtr<UHapticSequence>(newSeq));
				ImportedSequences.Add(sequence_name, newSeq);
				newSeq->PostEditChange();
			
			}
			
		}
		*HapticAsset = patternParent;
		return true;
		
	}

	return false;
}
