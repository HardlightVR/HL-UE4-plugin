#include "HapticSuitPrivatePCH.h"

#include "UPlaybackHandleImpl.h"
#include "NSLoader.h"


void UPlaybackHandleImpl::Play()
{
	NSVR_PlaybackHandle_Command(m_handle, NSVR_PlaybackCommand::NSVR_PlaybackCommand_Play);
}

void UPlaybackHandleImpl::Pause()
{
	NSVR_PlaybackHandle_Command(m_handle, NSVR_PlaybackCommand::NSVR_PlaybackCommand_Pause);
}

void UPlaybackHandleImpl::Reset()
{
	NSVR_PlaybackHandle_Command(m_handle, NSVR_PlaybackCommand::NSVR_PlaybackCommand_Reset);
}

UPlaybackHandleImpl::UPlaybackHandleImpl(NSVR_Timeline* timeline, NSVR_System* system)
{
	NSVR_PlaybackHandle_Create(&m_handle);
	NSVR_Timeline_Transmit(timeline, system, m_handle);
}

UPlaybackHandleImpl::~UPlaybackHandleImpl()
{
	NSVR_PlaybackHandle_Release(&m_handle);
}
