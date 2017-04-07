#include "HapticSuitPrivatePCH.h"

#include "FTimelineImpl.h"

#include "NSLoader.h"
//#include "ITimelineEvent.h"

#include "FBasicHapticEvent.h"
#include "FPlaybackHandleImpl.h"

FTimelineImpl::FTimelineImpl(NSVR_System* systemPtr) :m_system(systemPtr)
{
	NSVR_Timeline_Create(&m_timeline, m_system);
}

FTimelineImpl::~FTimelineImpl()
{
	NSVR_Timeline_Release(&m_timeline);
}



void FTimelineImpl::Add(const FBasicHapticEvent & timelineEvent)
{
	NSVR_Event* eventPtr;
	NSVR_Event_Create(&eventPtr, NSVR_EventType_BasicHapticEvent);

	NSVR_Event_SetFloat(eventPtr, "strength", timelineEvent.Strength);
	NSVR_Event_SetFloat(eventPtr, "duration", timelineEvent.Duration);
	NSVR_Event_SetFloat(eventPtr, "time", timelineEvent.Time);
	NSVR_Event_SetInteger(eventPtr, "effect", timelineEvent.Effect);
	NSVR_Event_SetInteger(eventPtr, "area", timelineEvent.Area);

	NSVR_Timeline_AddEvent(m_timeline, eventPtr);
	NSVR_Event_Release(&eventPtr);

}

TUniquePtr<IPlaybackHandle> FTimelineImpl::Transmit()
{
	
	NSVR_PlaybackHandle* handle;
	NSVR_PlaybackHandle_Create(&handle);

	NSVR_Timeline_Transmit(m_timeline, handle);

	////-----v takes ownership 
	return TUniquePtr<IPlaybackHandle>(new FPlaybackHandleImpl(handle));

}


