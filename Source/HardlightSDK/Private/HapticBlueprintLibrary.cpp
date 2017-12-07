#include "HapticSuitPrivatePCH.h"
#include "HapticBlueprintLibrary.h"
#include "UHapticSequence.h"
#include "UHapticPattern.h"
#include "UHapticExperience.h"
#include "UPlaybackHandle.h"
#include "UPlaybackHandleImpl.h"
#include "FBasicHapticEvent.h"
#include <unordered_map>
#include <bitset>
#include "EAreaFlags.h"
bool UHapticBlueprintLibrary::IsConnectedToSuit()
{
	return FHapticSuitModule::Get().IsAtLeastOneDevicePresent();

}

bool UHapticBlueprintLibrary::PauseAllHaptics()
{
	return FHapticSuitModule::Get().PauseAllHaptics();

}


bool UHapticBlueprintLibrary::ResumeAllHaptics()
{
	return FHapticSuitModule::Get().ResumeAllHaptics();
}

bool UHapticBlueprintLibrary::ClearAllHaptics()
{
	return FHapticSuitModule::Get().ClearAllHaptics();

}

std::vector<uint32_t> AreaToRegion(int AreaFlag)
{
	static std::unordered_map<EAreaFlags, int> regions = {
		{ EAreaFlags::Chest_Left, hlvr_region_chest_left },
		{ EAreaFlags::Upper_Ab_Left, hlvr_region_upper_ab_left },
		{ EAreaFlags::Mid_Ab_Left, hlvr_region_middle_ab_left },
		{ EAreaFlags::Lower_Ab_Left, hlvr_region_lower_ab_left },
		{ EAreaFlags::Shoulder_Left, hlvr_region_shoulder_left },
		{ EAreaFlags::Upper_Arm_Left, hlvr_region_upper_arm_left },
		{ EAreaFlags::Forearm_Left, hlvr_region_lower_arm_left },
		{ EAreaFlags::Back_Left, hlvr_region_upper_back_left },
		{ EAreaFlags::Chest_Right, hlvr_region_chest_right },
		{ EAreaFlags::Upper_Ab_Right, hlvr_region_upper_ab_right },
		{ EAreaFlags::Mid_Ab_Right, hlvr_region_middle_ab_right },
		{ EAreaFlags::Lower_Ab_Right, hlvr_region_lower_ab_right },
		{ EAreaFlags::Shoulder_Right, hlvr_region_shoulder_right },
		{ EAreaFlags::Upper_Arm_Right, hlvr_region_upper_arm_right },
		{ EAreaFlags::Forearm_Right, hlvr_region_lower_arm_right },
		{ EAreaFlags::Back_Right, hlvr_region_upper_back_right }
	};

	//Ok, so we don't use AreaFlags in UE4 the way we do in Unity. Here, we use UE's bitflags tag.
	//For instance, Forearm_Left is 0, meaning the actual integer value is 1 << [0].
	//Upper_Arm_Left is 1, meaning the actual integer value is 1 << [1], all the way up to 1 << [23] for lower_ab_right.

	//So we test every bit in our incoming int (which was created by combining EAreaFlags)
	//and extract the original flag out of it. Then we look up the corresponding region and add that to our list. 

	std::vector<uint32_t> results;
	std::bitset<32> flag(AreaFlag);
	for (uint8 i = 0; i < 32; i++) {
		if (flag.test(i)) {
			EAreaFlags af = static_cast<EAreaFlags>(i);
			auto it = regions.find(af);
			if (it != regions.end()) {
				results.push_back(it->second);
			}
		}
	}

	return results;
}



void EncodeSequence(float timeOffset, const TUniquePtr<ITimeline>& timeline, const UHapticSequence* seq, int area) {
	for (const auto& item : seq->EffectArray) {
	//	UE_LOG(LogTemp, Warning, TEXT("Add effect: t=%.3f,  d=%.3f, s=%.3f, e=%d, a=%d"), timeOffset + item.Time, item.Duration, item.StaticStruct, (int)item.Effect, area);

		timeline->Add(FBasicHapticEvent(timeOffset + item.Time, item.Duration, item.Strength, (int)item.Effect, AreaToRegion(area)));
	}
}

void EncodePattern(float timeOffset, const TUniquePtr<ITimeline>& timeline, UHapticPattern* pat)
{
	for (auto& item : pat->SequenceArray) {
		auto seqPtr = item.Sequence.LoadSynchronous();
		if (seqPtr != nullptr) {
			EncodeSequence(timeOffset + item.Args.Time, timeline, seqPtr, item.Args.Area);
			//UE_LOG(LogTemp, Warning, TEXT("Add seq at time %.4f, area %d"), timeOffset + item.Args.Time, item.Args.Area);

		}
		else {
		//	UE_LOG(LogTemp, Warning, TEXT("The seq wasn't loaded"));

		}
	}
}

void EncodeExperience(float timeOffset, const TUniquePtr<ITimeline>& timeline, UHapticExperience* exp)
{
	for (auto& item : exp->PatternArray) {
		auto patPtr = item.Pattern.LoadSynchronous();
		if (patPtr != nullptr) {
			EncodePattern(timeOffset + item.Args.Time, timeline, patPtr);
		}
	}
}



UPlaybackHandle* UHapticBlueprintLibrary::CreateSequenceHandle(int32  area, UHapticSequence* seq)
{
	if (seq == NULL) {
		UE_LOG(LogTemp, Warning, TEXT("Can't create a handle from a null HapticSequence!"));
		return NULL;
	}
	auto timeline = FHapticSuitModule::Get().CreateTimeline();
	EncodeSequence(0, timeline, seq, area);
	auto handle = NewObject<UPlaybackHandle>();
	handle->ProvideHandleImplementation(timeline->Transmit());
	return handle;

}




UPlaybackHandle* UHapticBlueprintLibrary::CreatePatternHandle(UHapticPattern* pat)
{
	if (pat == NULL) {
		UE_LOG(LogTemp, Warning, TEXT("Can't create a handle from a null HapticPattern!"));
		return NULL;
	}
	auto timeline = FHapticSuitModule::Get().CreateTimeline();
	EncodePattern(0, timeline, pat);
	auto handle = NewObject<UPlaybackHandle>();
	handle->ProvideHandleImplementation(timeline->Transmit());
	return handle;

}

UPlaybackHandle* UHapticBlueprintLibrary::CreateExperienceHandle(UHapticExperience* exp)
{
	if (exp == NULL) {
		UE_LOG(LogTemp, Warning, TEXT("Can't create a handle from a null HapticExperience!"));

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
	for (int i = 0; i < 5; i++) {
		FBasicHapticEvent event(i*0.5f, 0.0, 1, (int)EEffects::Click, { hlvr_region_body });
		timeline->Add(event);
	}
	auto handle = timeline->Transmit();
	handle->Play();
	return true;

}
bool UHapticBlueprintLibrary::IsConnectedToService() {
	return FHapticSuitModule::Get().GetServiceInfo(nullptr);
}

