#pragma once
#include "Runtime/Core/Public/Templates/UniquePtr.h"

#include "ITimeline.h"
#include "IPlaybackHandle.h"

#include "bindings/cpp/hlvr_timeline.hpp"

struct FBasicHapticEvent;

class FTimelineImpl : public ITimeline {

public:
	explicit FTimelineImpl(hlvr::system* system);

	void Add(const FBasicHapticEvent& timelineEvent) override;
	TUniquePtr<IPlaybackHandle> Transmit() override;
private:
	hlvr::system* m_system;
	hlvr::timeline m_timeline;

};