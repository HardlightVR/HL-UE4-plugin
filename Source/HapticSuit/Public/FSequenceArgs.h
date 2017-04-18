// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once
#include "CoreMinimal.h"

#include "UObject/ObjectMacros.h"
#include "UObject/Object.h"
#include "EAreaFlags.h"
#include "FSequenceArgs.generated.h"


USTRUCT()
struct FSequenceArgs
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = Data)
	float Time;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (Bitmask, BitmaskEnum = "EAreaFlags"), Category = Data)
	int32 Area;
	


};