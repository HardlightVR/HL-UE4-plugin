// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once
#include "CoreMinimal.h"

#include "UObject/ObjectMacros.h"
#include "UObject/Object.h"
#include "FEffectStruct.h"
#include "Runtime/CoreUObject/Public/UObject/AssetPtr.h"

#include "EAreaFlags.h"
#include "Runtime/Core/Public/Containers/ContainersFwd.h"
#include "FSequencePair.h"
#include "UHapticPattern.generated.h"






UCLASS(Blueprintable, MinimalAPI)
class UHapticPattern : public UHapticAsset
{
	GENERATED_UCLASS_BODY()
	
public:
	UPROPERTY(EditAnywhere, Category = Data)
	float Time;
	UPROPERTY(EditAnywhere, Category = Data)
	TArray<FSequencePair> SequenceArray;


};