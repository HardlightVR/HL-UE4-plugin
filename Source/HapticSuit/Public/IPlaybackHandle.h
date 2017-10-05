#pragma once



class IPlaybackHandle  {

public:
	virtual void Play() = 0;
	virtual void Pause() = 0;
	virtual void Reset() = 0;

	virtual float ElapsedDuration() = 0;
	virtual float TotalDuration() = 0;
	virtual bool IsPlaying() = 0;
	virtual bool IsPaused() = 0;
	virtual bool IsFinished() = 0;

	virtual ~IPlaybackHandle() {};
};