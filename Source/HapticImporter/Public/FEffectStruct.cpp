// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "HapticImporterPrivatePCH.h"
#include "FEffectStruct.h"

FEffectStruct::FEffectStruct(double time, double duration, double strength, EEffects effect):
	Time(time),
	Duration(duration),
	Strength(strength),
	Effect(effect)
{

}

FEffectStruct::FEffectStruct()
{
}
