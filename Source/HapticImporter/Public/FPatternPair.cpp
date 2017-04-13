// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "HapticImporterPrivatePCH.h"
#include "FPatternPair.h"


FPatternPair::FPatternPair(FPatternArgs args, TAssetPtr<UHapticPattern> seq) :
	Args(args)
	, Pattern(seq)
{

}
