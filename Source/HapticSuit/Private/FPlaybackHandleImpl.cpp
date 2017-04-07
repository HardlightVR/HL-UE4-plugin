#include "HapticSuitPrivatePCH.h"

#include "FPlaybackHandleImpl.h"
#include "NSLoader.h"

void FPlaybackHandleImpl::Play()
{
	NSVR_PlaybackHandle_Command(m_handle, NSVR_PlaybackCommand::NSVR_PlaybackCommand_Play);
}

void FPlaybackHandleImpl::Pause()
{
	NSVR_PlaybackHandle_Command(m_handle, NSVR_PlaybackCommand::NSVR_PlaybackCommand_Pause);

}

void FPlaybackHandleImpl::Reset()
{
	NSVR_PlaybackHandle_Command(m_handle, NSVR_PlaybackCommand::NSVR_PlaybackCommand_Reset);
}

FPlaybackHandleImpl::FPlaybackHandleImpl(NSVR_PlaybackHandle* handle) : m_handle(handle)
{

}

FPlaybackHandleImpl::~FPlaybackHandleImpl()
{
	NSVR_PlaybackHandle_Release(&m_handle);
}
