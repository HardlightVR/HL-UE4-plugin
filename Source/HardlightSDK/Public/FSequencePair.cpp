// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "HapticSuitPrivatePCH.h"
#include "FSequencePair.h"


FSequencePair::FSequencePair(FSequenceArgs args, TSoftObjectPtr<UHapticSequence> seq) :
	Args(args)
	, Sequence(seq)
{

}
