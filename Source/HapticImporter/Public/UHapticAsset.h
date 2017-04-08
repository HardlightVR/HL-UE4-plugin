// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once
#include "CoreMinimal.h"

#include "UObject/ObjectMacros.h"
#include "UObject/Object.h"
#include "UHapticAsset.generated.h"
UCLASS(Blueprintable)
class UHapticAsset : public UObject
{
	GENERATED_UCLASS_BODY()
	
	public:	
	FString Name;

};