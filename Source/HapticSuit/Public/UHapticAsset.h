// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once
#include "CoreMinimal.h"

#include "UObject/ObjectMacros.h"
#include "UObject/Object.h"
#include "UHapticAsset.generated.h"

UCLASS(Blueprintable, MinimalAPI)
class UHapticAsset : public UObject
{
	GENERATED_BODY()
	
public:
	enum class EAssetType { Sequence, Pattern, Experience};
	
	EAssetType AssetType;

	UPROPERTY(VisibleAnywhere, Category = Data)
	FString EffectName;


};