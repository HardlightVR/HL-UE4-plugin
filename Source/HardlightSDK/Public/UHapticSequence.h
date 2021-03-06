// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once
#include "CoreMinimal.h"

#include "UObject/ObjectMacros.h"
#include "UObject/Object.h"
#include "FEffectStruct.h"
#include "UHapticAsset.h"
#include "UHapticSequence.generated.h"


UCLASS(Blueprintable, MinimalAPI)
class UHapticSequence : public UHapticAsset
{
	GENERATED_BODY()
	
public:
	

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (Bitmask, BitmaskEnum = "EAreaFlags"), Category = Data)
	//int32 Area;

	UPROPERTY(EditAnywhere, Category = Data)
	TArray<FEffectStruct> EffectArray;


};