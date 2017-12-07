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

	UFUNCTION(BlueprintCallable, Category = Hardlight)
	static UPlaybackHandle* CreateSequenceHandle(int32 area, UHapticSequence* sequence);

	UFUNCTION(BlueprintCallable, Category = Hardlight)
		static UPlaybackHandle* CreatePatternHandle(UHapticPattern* pattern);

	UFUNCTION(BlueprintCallable, Category = Hardlight)
		static UPlaybackHandle* CreateExperienceHandle(UHapticExperience* experience);

	UFUNCTION(BlueprintCallable, Category = Hardlight)
		static bool PlayTestRoutine();

	UFUNCTION(BlueprintCallable, Category = Hardlight)
		static bool IsConnectedToService();

	UFUNCTION(BlueprintCallable, Category = Hardlight)
		static bool IsConnectedToSuit();

	UFUNCTION(BlueprintCallable, Category = Hardlight)
		static bool PauseAllHaptics();
	UFUNCTION(BlueprintCallable, Category = Hardlight)
		static bool ResumeAllHaptics();
	UFUNCTION(BlueprintCallable, Category = Hardlight)
		static bool ClearAllHaptics();

	

};

