#pragma once



class IPlaybackHandle  {

public:
	virtual void Play() = 0;
	virtual void Pause() = 0;
	virtual void Reset() = 0;
	virtual ~IPlaybackHandle() {};
};