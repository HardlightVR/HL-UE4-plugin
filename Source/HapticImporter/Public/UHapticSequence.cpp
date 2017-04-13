// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "HapticImporterPrivatePCH.h"
#include "UHapticSequence.h"


UHapticSequence::UHapticSequence(const FObjectInitializer& ObjectInitializer) :Super(ObjectInitializer) {

}



void UHapticSequence::DoPopulateFromJson()
{
	auto sequence_data = RawData.GetObjectField("sequence_definitions")->GetArrayField(EffectName);
	for (const auto& item : sequence_data) {
		const auto& obj = item->AsObject();
		auto name = obj->GetStringField("effect");
		auto duration = obj->GetNumberField("duration");
		auto strength = obj->GetNumberField("strength");
		auto time = obj->GetNumberField("time");
		EffectArray.Add(FEffectStruct(time, duration, strength, EEffects::Bump));
	}
}
