#pragma once
#include "CoreMinimal.h"

#include "IPlaybackHandle.h"

#include "NSLoader_fwds.h"

class UPlaybackHandleImpl :  public IPlaybackHandle {
public:
	void Play() override;
	void Pause() override;
	void Reset() override;
	explicit UPlaybackHandleImpl(NSVR_Timeline* timeline, NSVR_System* system);
	~UPlaybackHandleImpl();
private:
	NSVR_PlaybackHandle* m_handle;
};