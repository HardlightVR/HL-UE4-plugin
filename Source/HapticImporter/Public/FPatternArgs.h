// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once
#include "CoreMinimal.h"

#include "UObject/ObjectMacros.h"
#include "UObject/Object.h"

#include "FPatternArgs.generated.h"


USTRUCT()
struct FPatternArgs
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = Data)
	float Time;



};