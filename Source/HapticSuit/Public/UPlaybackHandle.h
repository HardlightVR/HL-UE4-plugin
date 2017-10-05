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

	/** Gets whether the haptic handle is currently playing*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Is Finished Playing", Keywords = "playing complete ended done over end running active haptic handle hardlight"), Category = Hardlight)
		bool IsFinishedPlaying();

	/** Gets whether the haptic handle is currently playing*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Is Playing", Keywords = "playing running haptic handle hardlight"), Category = Hardlight)
		bool IsPlaying();

	/** Gets whether the haptic handle is currently playing*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Is Paused", Keywords = "playing paused halted interrupted frozen stalled haptic handle hardlight"), Category = Hardlight)
		bool IsPaused();

	/** Gets the current playing progress of the handle*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "ElapsedDuration", Keywords = "progress haptic handle hardlight"), Category = Hardlight)
		float ElapsedDuration();

	/** The total duration of the haptic handle */
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "TotalDuration", Keywords = "progress haptic handle hardlight"), Category = Hardlight)
		float TotalDuration();

	/** Gets the elapsed duration over the total duration 
	Clamped 0.0 to 1.0 */
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "PercentElapsed", Keywords = "percent progress haptic handle hardlight"), Category = Hardlight)
		float PercentElapsed();


	void ProvideHandleImplementation(TUniquePtr<IPlaybackHandle> handle);

	/** Gets whether the handle was set up using valid assets
	An invalid handle will not play anything*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "IsHandleEmpty", Keywords = "invalid null empty haptic handle hardlight"), Category = Hardlight)
	bool IsEmptyHandle();

private:
	TUniquePtr<IPlaybackHandle> m_handle;
};