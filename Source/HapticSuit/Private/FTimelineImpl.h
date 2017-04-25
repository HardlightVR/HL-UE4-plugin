#pragma once
#include "Runtime/Core/Public/Templates/UniquePtr.h"

#include "ITimeline.h"
#include "IPlaybackHandle.h"

#include "NSLoader_fwds.h"
struct FBasicHapticEvent;

class FTimelineImpl : public ITimeline {

public:
	explicit FTimelineImpl(NSVR_System* system);
	~FTimelineImpl();

	void Add(const FBasicHapticEvent& timelineEvent) override;
	TUniquePtr<IPlaybackHandle> Transmit() override;
private:
	NSVR_System* m_system;
	NSVR_Timeline* m_timeline;

};