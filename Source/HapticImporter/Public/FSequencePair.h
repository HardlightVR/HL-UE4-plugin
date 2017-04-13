// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once
#include "CoreMinimal.h"

#include "UObject/ObjectMacros.h"
#include "UObject/Object.h"
#include "FSequenceArgs.h"
#include "UHapticSequence.h"
#include "Runtime/CoreUObject/Public/UObject/AssetPtr.h"
#include "FSequencePair.generated.h"


USTRUCT()
struct FSequencePair
{
	GENERATED_BODY()

public:
	FSequencePair(FSequenceArgs args, TAssetPtr<UHapticSequence> seq);
	FSequencePair() {}
	UPROPERTY(EditAnywhere, Category = Data)
	FSequenceArgs Args;

	UPROPERTY(EditAnywhere, Category = Data)
	TAssetPtr<UHapticSequence> Sequence;
	

};