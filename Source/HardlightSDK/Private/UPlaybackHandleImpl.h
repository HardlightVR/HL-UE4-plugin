#pragma once
#include "CoreMinimal.h"

#include "IPlaybackHandle.h"

#include "bindings/cpp/hlvr_effect.hpp"
#include "bindings/cpp/hlvr_timeline.hpp"

class UPlaybackHandleImpl :  public IPlaybackHandle {
public:
	void Play() override;
	void Pause() override;
	void Reset() override;
	explicit UPlaybackHandleImpl(hlvr::effect effect);
private:
	hlvr::effect m_handle;
};