// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once
#include "CoreMinimal.h"

#include "UObject/ObjectMacros.h"
#include "UObject/Object.h"
#include "IPlaybackHandle.h"
#include "UPlaybackHandle.generated.h"



UCLASS(Blueprintable)
class UPlaybackHandle : public UObject
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable, Category = HapticSuit)
	UPlaybackHandle* Play();

	UFUNCTION(BlueprintCallable, Category = HapticSuit)
	UPlaybackHandle* Pause();

	UFUNCTION(BlueprintCallable, Category = HapticSuit)
	UPlaybackHandle* Stop();

	void ProvideHandleImplementation(TUniquePtr<IPlaybackHandle> handle);

private:
	TUniquePtr<IPlaybackHandle> m_handle;
};