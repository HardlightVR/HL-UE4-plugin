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
#include "UObject/UObjectGlobals.h"
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
	EffectsMap.Add("bump", EEffects::Bump);
	EffectsMap.Add("buzz", EEffects::Buzz);
	EffectsMap.Add("click", EEffects::Click);
	EffectsMap.Add("sharp_click", EEffects::Click);
	EffectsMap.Add("fuzz", EEffects::Fuzz);
	EffectsMap.Add("hum", EEffects::Hum);
	EffectsMap.Add("long_double_sharp_tick", EEffects::Double_Click);
	EffectsMap.Add("pulse", EEffects::Pulse);
	EffectsMap.Add("pulse_sharp", EEffects::Pulse);
	EffectsMap.Add("sharp_tick", EEffects::Tick);
	EffectsMap.Add("double_click", EEffects::Double_Click);
	EffectsMap.Add("short_double_click", EEffects::Double_Click);
	EffectsMap.Add("short_double_sharp_tick", EEffects::Double_Click);
	EffectsMap.Add("transition_click", EEffects::Click);
	EffectsMap.Add("transition_hum", EEffects::Hum);
	EffectsMap.Add("triple_click", EEffects::Triple_Click);

	AreasMap.Add("Forearm_Left", (1 << 0));
	AreasMap.Add("Upper_Arm_Left", (1 << 1));
	AreasMap.Add("Shoulder_Left", (1 << 2));
	AreasMap.Add("Back_Left", (1 << 3));
	AreasMap.Add("Chest_Left", (1 << 4));
	AreasMap.Add("Upper_Ab_Left", (1 << 5));
	AreasMap.Add("Mid_Ab_Left", (1 << 6));
	AreasMap.Add("Lower_Ab_Left", (1 << 7));
	AreasMap.Add("Forearm_Right", (1 << 16));
	AreasMap.Add("Upper_Arm_Right", (1 << 17));
	AreasMap.Add("Shoulder_Right", (1 << 18));
	AreasMap.Add("Back_Right", (1 << 19));
	AreasMap.Add("Chest_Right", (1 << 20));
	AreasMap.Add("Upper_Ab_Right", (1 << 21));
	AreasMap.Add("Mid_Ab_Right", (1 << 22));
	AreasMap.Add("Lower_Ab_Right", (1 << 23));

	/* Should support..? Unknown yet*/
	AreasMap.Add("Forearm_Both", *AreasMap.Find("Forearm_Left") | *AreasMap.Find("Forearm_Right"));
	AreasMap.Add("Upper_Arm_Both", *AreasMap.Find("Upper_Arm_Left") | *AreasMap.Find("Upper_Arm_Right"));
	AreasMap.Add("Shoulder_Both", *AreasMap.Find("Shoulder_Left") | *AreasMap.Find("Shoulder_Right"));
	AreasMap.Add("Back_Both", *AreasMap.Find("Back_Left") | *AreasMap.Find("Back_Right"));
	AreasMap.Add("Chest_Both", *AreasMap.Find("Chest_Left") | *AreasMap.Find("Chest_Right"));
	AreasMap.Add("Upper_Ab_Both", *AreasMap.Find("Upper_Ab_Left") | *AreasMap.Find("Upper_Ab_Right"));
	AreasMap.Add("Mid_Ab_Both", *AreasMap.Find("Mid_Ab_Left") | *AreasMap.Find("Mid_Ab_Right"));
	AreasMap.Add("Lower_Ab_Both", *AreasMap.Find("Lower_Ab_Left") | *AreasMap.Find("Lower_Ab_Right"));

	AreasMap.Add("Left_All",  0x000000FF);
	AreasMap.Add("Right_All", 0x00FF0000);
	AreasMap.Add("All_Areas", *AreasMap.Find("Left_All") | *AreasMap.Find("Right_All"));

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

bool FHapticAssetImporter::ParseSequence(UHapticSequence* sequence) {
	auto sequence_data = RawData.GetObjectField("sequence_definitions")->GetArrayField(sequence->EffectName);
	for (const auto& item : sequence_data) {
		const auto& obj = item->AsObject();
		EEffects actualval = EEffects::Click;
		auto potentialEffect = EffectsMap.Find(obj->GetStringField("effect"));
		if (potentialEffect != nullptr) {
			actualval = *potentialEffect;
		}
		else {
			FString a = obj->GetStringField("effect");
			UE_LOG(LogTemp, Warning, TEXT("Tried to parse an unknown effec: %s"), *a );

		}

		auto duration = obj->GetNumberField("duration");
		auto strength = obj->GetNumberField("strength");
		auto time = obj->GetNumberField("time");
		sequence->EffectArray.Add(FEffectStruct(time, duration, strength, actualval));
	}
	return true;
}

void FHapticAssetImporter::ParsePattern(UHapticPattern* pattern)
{
	auto pattern_data = RawData.GetObjectField("pattern_definitions")->GetArrayField(pattern->EffectName);

	for (const auto& node : pattern_data) {
		const auto& nodeObj = node->AsObject();
		FSequenceArgs Args;
		Args.Area = ParseArea(nodeObj->GetStringField("area"));
		Args.Time = nodeObj->GetNumberField("time");
		const auto& seq_name = nodeObj->GetStringField("sequence");
		//ADD STRENGTH
		pattern->SequenceArray.Add(FSequencePair(Args, TAssetPtr<UHapticSequence>(*ImportedSequences.Find(seq_name))));
	}
}

void FHapticAssetImporter::ParseExperience(UHapticExperience* experience)
{
	auto experience_data = RawData.GetObjectField("experience_definitions")->GetArrayField(experience->EffectName);
	for (const auto& node : experience_data) {
		const auto& nodeObj = node->AsObject();
		FPatternArgs Args;
		Args.Time = nodeObj->GetNumberField("time");
		const auto& pat_name = nodeObj->GetStringField("pattern");
		experience->PatternArray.Add(FPatternPair(Args, TAssetPtr<UHapticPattern>(*ImportedPatterns.Find(pat_name))));
	}
}


int32 FHapticAssetImporter::ParseArea(const FString& areaString)
{
	TArray<FString> Tokens;
	areaString.ParseIntoArray(Tokens, TEXT("|"), 1);
	int32 result = 0;
	for (FString token : Tokens) {
		FString cleanedUp = token.Trim().TrimTrailing();
		auto potentialEnum = AreasMap.Find(cleanedUp);
		if (potentialEnum != nullptr) {
			result |= *potentialEnum;
		}
	}
	
	return result;
	
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

	/*UPackage* HapticsPackage = CreatePackage(InParent, TEXT("Haptics"));
	UPackage* PatternPackage = CreatePackage(HapticsPackage, TEXT("patterns"));
	UPackage* SequencePackage = CreatePackage(HapticsPackage, TEXT("sequences"));
	UPackage* ExperiencePackage = CreatePackage(HapticsPackage, TEXT("experiences"));*/


	const auto& SequenceDefinitions = RawData.GetObjectField("sequence_definitions");
	const auto& PatternDefinitions = RawData.GetObjectField("pattern_definitions");
	const auto& ExperienceDefinitions = RawData.GetObjectField("experience_definitions");

	for (const auto& sequence : SequenceDefinitions->Values) {
		if (!ImportedSequences.Contains(sequence.Key)) {
			UHapticSequence* NewSequence = CreateNewSequence(sequence.Key, InParent, Flags);
			NewSequence->RawData = RawData;
			NewSequence->EffectName = sequence.Key;
			ParseSequence(NewSequence);
			ImportedSequences.Add(sequence.Key, NewSequence);
		}
	}

	for (const auto& pattern : PatternDefinitions->Values) {
		if (!ImportedPatterns.Contains(pattern.Key)) {
			UHapticPattern* NewPattern = CreateNewPattern(pattern.Key, InParent, Flags);
			NewPattern->RawData = RawData;
			NewPattern->EffectName = pattern.Key;
			ParsePattern(NewPattern);
			ImportedPatterns.Add(pattern.Key, NewPattern);
		}
	}

	for (const auto& experience : ExperienceDefinitions->Values) {
		if (!ImportedExperiences.Contains(experience.Key)) {
			UHapticExperience* NewExperience = CreateNewExperience(experience.Key, InParent, Flags);
			NewExperience->RawData = RawData;
			NewExperience->EffectName = experience.Key;
			ParseExperience(NewExperience);
			ImportedExperiences.Add(experience.Key, NewExperience);
		}
	}

	switch (AssetType) {
	case UHapticAsset::EAssetType::Sequence:
		*HapticAsset = *ImportedSequences.Find(RootKey);
		return true;
	case UHapticAsset::EAssetType::Pattern:
		*HapticAsset = *ImportedPatterns.Find(RootKey);
		return true;
	case UHapticAsset::EAssetType::Experience:
		*HapticAsset = *ImportedExperiences.Find(RootKey);
		return true;
	default:
		return false;
	}


}
