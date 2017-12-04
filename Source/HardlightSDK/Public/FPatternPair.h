// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once
#include "CoreMinimal.h"

#include "UObject/ObjectMacros.h"
#include "UObject/Object.h"
#include "FPatternArgs.h"
#include "UHapticPattern.h"
#include "Runtime/CoreUObject/Public/UObject/SoftObjectPtr.h"
#include "FPatternPair.generated.h"


USTRUCT()
struct HARDLIGHTSDK_API FPatternPair
{
	GENERATED_BODY()

public:
	FPatternPair(FPatternArgs args, TSoftObjectPtr<UHapticPattern> seq);
	FPatternPair() {}
	UPROPERTY(EditAnywhere, Category = Data)
	FPatternArgs Args;

	UPROPERTY(EditAnywhere, Category = Data)
	TSoftObjectPtr<UHapticPattern> Pattern;
	

};