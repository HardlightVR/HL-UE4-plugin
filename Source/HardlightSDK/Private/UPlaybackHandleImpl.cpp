#include "HapticSuitPrivatePCH.h"

#include "UPlaybackHandleImpl.h"


void UPlaybackHandleImpl::Play()
{
	check(m_handle);
	m_handle.play();
}

void UPlaybackHandleImpl::Pause()
{
	check(m_handle);
	m_handle.pause();

}

void UPlaybackHandleImpl::Reset()
{
	check(m_handle);
	m_handle.reset();
}

UPlaybackHandleImpl::UPlaybackHandleImpl(hlvr::effect effect)
{
	m_handle = std::move(effect);

	
}

