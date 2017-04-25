#pragma once
//#include "CoreMinimal.h"
//#include "ITimelineEvent.h"
#include "Runtime/Core/Public/Templates/UniquePtr.h"

#include "IPlaybackHandle.h"

struct FBasicHapticEvent;
class ITimeline {
public:
	virtual void Add(const FBasicHapticEvent& event) = 0;
	virtual TUniquePtr<IPlaybackHandle> Transmit() = 0;
	virtual ~ITimeline() {};
};