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

void UPlaybackHandle::ProvideHandleImplementation(TUniquePtr<IPlaybackHandle> handle)
{
	m_handle = std::move(handle);
}
