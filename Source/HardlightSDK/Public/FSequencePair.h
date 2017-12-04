// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once
#include "CoreMinimal.h"

#include "UObject/ObjectMacros.h"
#include "UObject/Object.h"
#include "FSequenceArgs.h"
#include "UHapticSequence.h"
#include "Runtime/CoreUObject/Public/UObject/SoftObjectPtr.h"
#include "FSequencePair.generated.h"


USTRUCT()
struct  HARDLIGHTSDK_API FSequencePair
{
	GENERATED_BODY()

public:
	FSequencePair(FSequenceArgs args, TSoftObjectPtr<UHapticSequence> seq);
	FSequencePair() {}
	UPROPERTY(EditAnywhere, Category = Data)
	FSequenceArgs Args;

	UPROPERTY(EditAnywhere, Category = Data)
	TSoftObjectPtr<UHapticSequence> Sequence;
	

};