// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once
#include "CoreMinimal.h"

#include "UObject/ObjectMacros.h"
#include "UObject/Object.h"
#include "Runtime/Json/Public/Dom/JsonObject.h"
#include "UHapticAsset.generated.h"


UCLASS(Blueprintable)
class UHapticAsset : public UObject
{
	GENERATED_UCLASS_BODY()
	
public:
	enum class EAssetType { Sequence, Pattern, Experience};

public:
	
	FJsonObject RawData;
	EAssetType AssetType;

	UPROPERTY(VisibleAnywhere, Category = Data)
	FString EffectName;

	void PopulateDataFromJson();
private:
	virtual void DoPopulateFromJson() {};
};