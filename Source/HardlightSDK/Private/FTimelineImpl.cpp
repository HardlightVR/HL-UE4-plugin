#include "HapticSuitPrivatePCH.h"

#include "FTimelineImpl.h"
#include "FBasicHapticEvent.h"
#include "UPlaybackHandleImpl.h"
#include "bindings/cpp/hlvr_event.hpp"

FTimelineImpl::FTimelineImpl(hlvr::system* systemPtr) :m_system(systemPtr)
{
	m_timeline = *hlvr::timeline::make();
	check(m_timeline);
	UE_LOG(LogTemp, Warning, TEXT("Timeline created succesfully"));

}




template<typename T, typename O>
std::vector<T> vec_cast(const std::vector<O>& in) {
	std::vector<T> result;
	for (const auto& val : in) {
		result.push_back(static_cast<T>(val));
	}

	return result;
}
void FTimelineImpl::Add(const FBasicHapticEvent & timelineEvent)
{
	hlvr::event event = *hlvr::event::make(HLVR_EventType_DiscreteHaptic);
	check(event);
	UE_LOG(LogTemp, Warning, TEXT("Event created succesfully"));

	event.set_float(HLVR_EventKey_DiscreteHaptic_Strength_Float, timelineEvent.Strength);
	event.set_float(HLVR_EventKey_DiscreteHaptic_Repetitions_UInt32, timelineEvent.Duration / 0.25f);
	event.set_int(HLVR_EventKey_DiscreteHaptic_Waveform_Int, timelineEvent.Effect);

	event.set_uint32s(HLVR_EventKey_Target_Regions_UInt32s, timelineEvent.Regions.data(), timelineEvent.Regions.size() );

	check(m_timeline);
	m_timeline.add_event(event, timelineEvent.Time);

}

TUniquePtr<IPlaybackHandle> FTimelineImpl::Transmit()
{
	check(m_timeline);
	check(m_system);
	hlvr::effect eff = *m_timeline.transmit(*m_system);
	check(eff);

	UE_LOG(LogTemp, Warning, TEXT("Timeline transmitted succesfully"));

	return TUniquePtr<IPlaybackHandle>(new UPlaybackHandleImpl(std::move(eff)));
}


