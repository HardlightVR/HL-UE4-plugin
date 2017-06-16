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

	/** Plays this Haptic Handle if it has valid content.
	If there is invalid content, it will play nothing. */
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Play", Keywords = "play haptic handle hardlight"), Category = Hardlight)
	UPlaybackHandle* Play();

	/** Sets the playing state to stopped. Does not disrupt the playing progress.
	Resume from Pause() with Play().*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Pause", Keywords = "pause interrupt wait haptic handle hardlight"), Category = Hardlight)
	UPlaybackHandle* Pause();

	/** Sets the playing state to stopped. Removes any playing progress. */
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Stop", Keywords = "stop reset end halt haptic handle hardlight"), Category = Hardlight)
	UPlaybackHandle* Stop();

	/** Restarts the effect at time 0 in the playing state.
	Identical to calling Stop->Play*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Restart", Keywords = "restart reset replay haptic handle hardlight"), Category = Hardlight)
		UPlaybackHandle* Restart();

	void ProvideHandleImplementation(TUniquePtr<IPlaybackHandle> handle);

private:
	TUniquePtr<IPlaybackHandle> m_handle;
};