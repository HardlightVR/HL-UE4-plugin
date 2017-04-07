#pragma once

#include "IPlaybackHandle.h"

#include "NSLoader_fwds.h"

class FPlaybackHandleImpl : public IPlaybackHandle {
public:
	void Play() override;
	void Pause() override;
	void Reset() override;
	//assumes owernship
	explicit FPlaybackHandleImpl(NSVR_PlaybackHandle* timeline);
	~FPlaybackHandleImpl();
private:
	NSVR_PlaybackHandle* m_handle;
};