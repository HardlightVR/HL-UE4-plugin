// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "HapticSuitPrivatePCH.h"
#include "UPlaybackHandle.h"


UPlaybackHandle* UPlaybackHandle::Play()
{
	m_handle->Play();
	return &*this;
}

UPlaybackHandle* UPlaybackHandle::Pause()
{
	m_handle->Pause();
	return &*this;
}

UPlaybackHandle* UPlaybackHandle::Stop()
{
	m_handle->Reset();
	return &*this;
}

UPlaybackHandle* UPlaybackHandle::Restart()
{
	m_handle->Reset();
	m_handle->Play();
	return &*this;
}

bool UPlaybackHandle::IsFinishedPlaying()
{
	return m_handle->IsFinished();
}

bool UPlaybackHandle::IsPlaying()
{
	return m_handle->IsPlaying();
}

bool UPlaybackHandle::IsPaused()
{
	return m_handle->IsPaused();
}

float UPlaybackHandle::ElapsedDuration()
{
	return m_handle->ElapsedDuration();
}

float UPlaybackHandle::TotalDuration()
{
	return m_handle->TotalDuration();
}

float UPlaybackHandle::PercentElapsed()
{
	return m_handle->ElapsedDuration() / m_handle->TotalDuration();
}

bool UPlaybackHandle::IsEmptyHandle()
{
	return !m_handle.IsValid();
}

void UPlaybackHandle::ProvideHandleImplementation(TUniquePtr<IPlaybackHandle> handle)
{
	m_handle = MoveTemp(handle);
}
