#pragma once
#include "CoreMinimal.h"

#include "IPlaybackHandle.h"

#include "NSLoader_fwds.h"

class UPlaybackHandleImpl : public IPlaybackHandle {
public:
	void Play() override;
	void Pause() override;
	void Reset() override;

	float ElapsedDuration() override;
	float TotalDuration() override;
	bool IsPlaying() override;
	bool IsPaused() override;
	bool IsFinished() override;

	explicit UPlaybackHandleImpl(NSVR_Timeline* timeline, NSVR_System* system);
	~UPlaybackHandleImpl();
private:
	NSVR_PlaybackHandle* m_handle;
};