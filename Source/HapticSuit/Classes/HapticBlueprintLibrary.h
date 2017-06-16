// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "HapticSuit.h"
#include "UObject/ObjectMacros.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CoreMinimal.h"
#include "Runtime/Core/Public/Templates/SharedPointer.h"
#include "IPlaybackHandle.h"
#include "EAreaFlags.h"
#include "HapticBlueprintLibrary.generated.h"

class UHapticSequence;
class UPlaybackHandle;
class UHapticExperience;
class UHapticPattern;

UENUM(BlueprintType)
enum class HapticFileType : uint8
{
	Sequence		UMETA(DisplayName = "Sequence on Areas"),
	SequenceOnAll	UMETA(DisplayName = "Sequence on All"),
	Pattern			UMETA(DisplayName = "Pattern"),
	Experience		UMETA(DisplayName = "Experience")
};


UCLASS()
class UHapticBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	//IMPORTANT NOTE: The /** [Content] */ block comments are parsed as the Unreal Tooltips for each of these UFUNCTIONs.
	//Keep them up to date!

	/** Creates a Playback Handle with the requested Sequence on the targeted area(s).
	Remember to call the Handle's Play/Stop nodes to Start and End the effect. */
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Create Sequence Handle", Keywords = "hardlight haptic playback handle seq sequence"), Category = Hardlight)
		static UPlaybackHandle* CreateSequenceHandle(int32 area, UHapticSequence* sequence);

	/** Creates a Playback Handle with the requested Pattern.
	Remember to call the Handle's Play/Stop nodes to Start and End the effect. */
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Create Pattern Handle", Keywords = "hardlight haptic playback handle pat pattern"), Category = Hardlight)
		static UPlaybackHandle* CreatePatternHandle(UHapticPattern* pattern);

	/** Creates a Playback Handle with the requested Experience.
	Remember to call the Handle's Play/Stop nodes to Start and End the effect. */
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Create Experience Handle", Keywords = "hardlight haptic playback handle exp experience"), Category = Hardlight)
		static UPlaybackHandle* CreateExperienceHandle(UHapticExperience* experience);

	/** Plays a simple test routine to make sure Unreal Haptics work.
	Manually creates a timeline and adds 5 clicks to it. */
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Play Test Routine", Keywords = "hardlight test demo routine haptic"), Category = Hardlight)
		static bool PlayTestRoutine();

	/** Returns true if we are connected to the NullSpace Service
	Service must be running & enabled for haptics to work */
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Connected To NullSpace Service", Keywords = "hardlight haptic service nullspace connected"), Category = Hardlight)
		static bool IsConnectedToService();

	//Hidden while it is not yet implemented.
	/** Attempts to launch the NullSpace Service */
	//UFUNCTION(BlueprintCallable, meta = (DisplayName = "Launch NullSpace Service", Keywords = "hardlight haptic service launch start nullspace connected"), Category = Hardlight)
		static void LaunchService();

	/** Returns true if the NullSpace Service is currently connected to a suit.
	Returns false if service is off or suit is disconnected. */
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Connected to Hardlight Suit", Keywords = "hardlight haptic service suit connected"), Category = Hardlight)
		static bool IsConnectedToSuit();

	/** Initiates a game-wide suspension of the haptics system
	Intended to be used for full-game pausing (alt-tab, etc)
	You can still create Haptics after calling this (they will also be suspended).
	Suspended haptics remain suspended regardless of the PlaybackHandle Resume Node*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Suspend All Haptics", Keywords = "freeze frozen hardlight haptic haptics"), Category = Hardlight)
		static bool SuspendAllHaptics();

	/** Ends a game-wide suspension of the haptics system
	Intended to be used to end full-game pausing
	Does not affect Handle Paused effects */
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Resume All Haptics", Keywords = "unfreeze thaw hardlight play haptic haptics"), Category = Hardlight)
		static bool ResumeAllHaptics();

	/** Removes all haptics effects from the system
	Call when you change scenes or quit your game.
	This will invalidate your Playback Handles. */
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Clear All Haptics", Keywords = "clear remove shutdown end stop halt all hardlight haptic haptics"), Category = Hardlight)
		static bool ClearAllHaptics();
};

