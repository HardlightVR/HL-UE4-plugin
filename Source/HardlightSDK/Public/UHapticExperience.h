// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once
#include "CoreMinimal.h"

#include "UObject/ObjectMacros.h"
#include "UObject/Object.h"
#include "FEffectStruct.h"
#include "FPatternPair.h"
#include "UHapticExperience.generated.h"


UCLASS(Blueprintable, MinimalAPI)
class UHapticExperience : public UHapticAsset
{
	GENERATED_UCLASS_BODY()
	
public:
	UPROPERTY(EditAnywhere, Category = Data)
	float Time;



	//worry about parameterizing area later

	UPROPERTY(EditAnywhere, Category = Data)
	TArray<FPatternPair> PatternArray;

};