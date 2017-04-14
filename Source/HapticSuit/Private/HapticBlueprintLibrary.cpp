#include "HapticSuitPrivatePCH.h"
#include "HapticBlueprintLibrary.h"
#include "UHapticSequence.h"
#include "UHapticPattern.h"
#include "UHapticExperience.h"
#include "UPlaybackHandle.h"
#include "UPlaybackHandleImpl.h"
#include "FBasicHapticEvent.h"
#include "Runtime/CoreUObject/Public/UObject/AssetPtr.h"
#include "NSLoader.h"
bool UHapticBlueprintLibrary::IsConnectedToSuit()
{
	return FHapticSuitModule::Get().GetDeviceInfo(nullptr);

}


void EncodeSequence(float timeOffset, const TUniquePtr<ITimeline>& timeline, const UHapticSequence* seq, int area) {
	for (const auto& item : seq->EffectArray) {
		timeline->Add(FBasicHapticEvent(timeOffset + item.Time, item.Duration, item.Strength, (int)item.Effect, area));
	}
}

void EncodePattern(float timeOffset, const TUniquePtr<ITimeline>& timeline, UHapticPattern* pat)
{
	for (const auto& item : pat->SequenceArray) {
		auto seqPtr = item.Sequence.Get();
		if (seqPtr != nullptr) {
			EncodeSequence(timeOffset + item.Args.Time, timeline, seqPtr, item.Args.Area);
			UE_LOG(LogTemp, Warning, TEXT("Add seq at time %.4f, area %d"), timeOffset+item.Args.Time, item.Args.Area);

		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("The seq wasn't loaded"));

		}
	}
}

void EncodeExperience(float timeOffset, const TUniquePtr<ITimeline>& timeline, UHapticExperience* exp)
{
	for (const auto& item : exp->PatternArray) {
		auto patPtr = item.Pattern.Get();
		if (patPtr != nullptr) {
			EncodePattern(timeOffset + item.Args.Time, timeline, patPtr);
		}
	}
}

UPlaybackHandle* UHapticBlueprintLibrary::CreateSequenceHandle(int32  area, UHapticSequence* seq)
{
	UE_LOG(LogTemp, Warning, TEXT("Value of area enum: %d"), area);
	auto timeline = FHapticSuitModule::Get().CreateTimeline();


	EncodeSequence(0, timeline, seq, area);


	auto handle = NewObject<UPlaybackHandle>();
	handle->ProvideHandleImplementation(timeline->Transmit());
	return handle;

}




UPlaybackHandle* UHapticBlueprintLibrary::CreatePatternHandle(UHapticPattern* pat)
{
	auto timeline = FHapticSuitModule::Get().CreateTimeline();
	EncodePattern(0, timeline, pat);
	auto handle = NewObject<UPlaybackHandle>();
	handle->ProvideHandleImplementation(timeline->Transmit());
	return handle;

}

UPlaybackHandle* UHapticBlueprintLibrary::CreateExperienceHandle(UHapticExperience* exp)
{
	auto timeline = FHapticSuitModule::Get().CreateTimeline();
	EncodeExperience(0, timeline, exp);
	auto handle = NewObject<UPlaybackHandle>();
	handle->ProvideHandleImplementation(timeline->Transmit());
	return handle;

}

bool UHapticBlueprintLibrary::PlayTestRoutine() {
	auto timeline = FHapticSuitModule::Get().CreateTimeline();
	for (int i = 0; i < 10; i++) {
		FBasicHapticEvent event(i*0.5f, 0.2, 1, 666, 1048576);
		timeline->Add(event);
	}
	auto handle = timeline->Transmit();
	handle->Play();
	return true;

}
bool UHapticBlueprintLibrary::IsConnectedToService() {
	return FHapticSuitModule::Get().GetServiceInfo(nullptr);
}
bool UHapticBlueprintLibrary::PluginLoadedSuccessfully()
{
	return FHapticSuitModule::Get().PluginLoadedSuccessfully();
}

void UHapticBlueprintLibrary::ResetPlugin()
{
	//FHapticSuitModule::Get().ResetPlugin();
}

bool UHapticBlueprintLibrary::PlayHaptic(FString HapticEffectName, HapticFileType fileType, int32 Where)
{
	if (fileType == HapticFileType::Sequence)
	{
		return PlayHapticSequence(HapticEffectName, Where);
	}
	else if (fileType == HapticFileType::SequenceOnAll)
	{
		return PlayHapticSequenceOnAll(HapticEffectName);
	}
	else if (fileType == HapticFileType::Pattern)
	{
		return PlayHapticPattern(HapticEffectName);
	}
	else if (fileType == HapticFileType::Experience)
	{
		return PlayHapticExperience(HapticEffectName);
	}
	return false;
}

bool UHapticBlueprintLibrary::PlayHapticSequenceOnAll(FString HapticEffectName)
{
	return FHapticSuitModule::Get().LoadAndPlaySequenceOnAll(HapticEffectName);
}

bool UHapticBlueprintLibrary::PlayHapticSequence(FString HapticEffectName, int32 Where)
{
	return FHapticSuitModule::Get().LoadAndPlaySequence(HapticEffectName, Where);
}

bool UHapticBlueprintLibrary::PlayHapticPattern(FString HapticEffectName)
{
	return FHapticSuitModule::Get().LoadAndPlayPattern(HapticEffectName);
}

bool UHapticBlueprintLibrary::PlayHapticExperience(FString HapticEffectName)
{
	return FHapticSuitModule::Get().LoadAndPlayExperience(HapticEffectName);
}

void UHapticBlueprintLibrary::ClearAllHaptics()
{
	FHapticSuitModule::Get().ClearAllHaptics();
}