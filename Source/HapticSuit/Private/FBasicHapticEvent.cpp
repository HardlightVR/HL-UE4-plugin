#include "HapticSuitPrivatePCH.h"

#include "FBasicHapticEvent.h"

FBasicHapticEvent::FBasicHapticEvent(float time, float duration, float strength, int effect, int area):	
	Time(time),
Duration(duration),
Strength(strength),
Effect(effect), Area(area) {}

