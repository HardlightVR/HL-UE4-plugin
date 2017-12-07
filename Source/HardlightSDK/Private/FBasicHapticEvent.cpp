#include "HapticSuitPrivatePCH.h"

#include "FBasicHapticEvent.h"

FBasicHapticEvent::FBasicHapticEvent(float time, float duration, float strength, int effect, std::vector<uint32_t> area):	
	Time(time),
	Duration(duration),
	Strength(strength),
	Effect(effect), Regions(std::move(area)) {}

