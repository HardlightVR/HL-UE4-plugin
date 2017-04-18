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
		UE_LOG(LogTemp, Warning, TEXT("Add effect: t=%.3f,  d=%.3f, s=%.3f, e=%d, a=%d"), timeOffset + item.Time, item.Duration, item.StaticStruct, (int)item.Effect, area);

		timeline->Add(FBasicHapticEvent(timeOffset + item.Time, item.Duration, item.Strength, (int)item.Effect, area));
	}
}

void EncodePattern(float timeOffset, const TUniquePtr<ITimeline>& timeline, UHapticPattern* pat)
{
	for (const auto& item : pat->SequenceArray) {
		auto seqPtr = item.Sequence.Get();
		if (seqPtr != nullptr) {
			EncodeSequence(timeOffset + item.Args.Time, timeline, seqPtr, item.Args.Area);
			UE_LOG(LogTemp, Warning, TEXT("Add seq at time %.4f, area %d"), timeOffset + item.Args.Time, item.Args.Area);

		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("The seq wasn't loaded"));

		}
	}
}
void AddThing(float timeOffset, const TUniquePtr<ITimeline>& timeline) {
	timeline->Add(FBasicHapticEvent(timeOffset, 0.2, 1.0, 666, 1048576));
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
	if (exp == NULL) {
		return NULL;
	}

	auto timeline = FHapticSuitModule::Get().CreateTimeline();

	EncodeExperience(0, timeline, exp);

	auto handle = timeline->Transmit();
	
	auto oHandle = NewObject<UPlaybackHandle>();
	oHandle->ProvideHandleImplementation(MoveTemp(handle));


	return oHandle;

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

