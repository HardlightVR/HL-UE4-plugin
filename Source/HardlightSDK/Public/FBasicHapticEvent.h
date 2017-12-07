#pragma once
#include <vector>
struct FBasicHapticEvent {
	float Time;
	float Duration;
	float Strength;
	int Effect;
	std::vector<uint32_t> Regions;

	FBasicHapticEvent(float time, float duration, float strength, int effect, std::vector<uint32_t> regions);
	
};