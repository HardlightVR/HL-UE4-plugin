#pragma once
#include "Runtime/Core/Public/Templates/UniquePtr.h"


#include "ITimeline.h"
class IHapticEventDrivenDevice
{
public:
	virtual TUniquePtr<ITimeline> CreateTimeline() = 0;
	virtual ~IHapticEventDrivenDevice() {}

};