#pragma once

struct FBasicHapticEvent {
	float Time;
	float Duration;
	float Strength;
	int Effect;
	int Area;

	FBasicHapticEvent(float time, float duration, float strength, int effect, int area);
	
};