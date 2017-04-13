// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "HapticImporterPrivatePCH.h"
#include "FSequencePair.h"


FSequencePair::FSequencePair(FSequenceArgs args, TAssetPtr<UHapticSequence> seq) :
	Args(args)
	, Sequence(seq)
{

}
