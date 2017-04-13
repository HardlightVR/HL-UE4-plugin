#include "HapticSuitPrivatePCH.h"
#include "HapticBlueprintLibrary.h"
#include "UHapticSequence.h"
#include "UPlaybackHandle.h"
#include "UPlaybackHandleImpl.h"
#include "FBasicHapticEvent.h"
#include "NSLoader.h"
bool UHapticBlueprintLibrary::IsConnectedToSuit()
{
	return FHapticSuitModule::Get().GetDeviceInfo(nullptr);

}


void EncodeSequence(float timeOffset, const TUniquePtr<ITimeline>& timeline, UHapticSequence* seq, int area) {
	for (const auto& item : seq->EffectArray) {
		timeline->Add(FBasicHapticEvent(timeOffset + item.Time, item.Duration, item.Strength, (int)item.Effect, area));
	}
}

//void EncodePattern(float timeOffset, const TUniquePtr<ITimeline>& timeline, UHapticPattern* pat) {

///}
UPlaybackHandle* UHapticBlueprintLibrary::CreateHandle(int32  area, UHapticSequence* seq)
{
	UE_LOG(LogTemp, Warning, TEXT("Value of area enum: %d"), area);
	auto timeline = FHapticSuitModule::Get().CreateTimeline();


	EncodeSequence(0, timeline, seq, area);


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