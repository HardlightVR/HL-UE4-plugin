// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once
#include "CoreMinimal.h"

#include "UObject/ObjectMacros.h"
#include "UObject/Object.h"
#include "FEffectStruct.h"
#include "UHapticAsset.h"
#include "UHapticSequence.generated.h"



UCLASS(Blueprintable)
class UHapticSequence : public UHapticAsset
{
	GENERATED_UCLASS_BODY()
	
public:
	UPROPERTY(EditAnywhere, Category = Data)
	float Time;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (Bitmask, BitmaskEnum = "EAreaFlags"), Category = Data)
	//int32 Area;

	UPROPERTY(EditAnywhere, Category = Data)
	TArray<FEffectStruct> EffectArray;



private:
	void DoPopulateFromJson() override;
};