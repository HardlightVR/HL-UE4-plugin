// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "HapticSuitPrivatePCH.h"
#include "HapticBlueprintLibrary.generated.h"

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

	UFUNCTION(BlueprintCallable, Category = HapticSuit)
		static bool PluginLoadedSuccessfully();

	UFUNCTION(BlueprintCallable, Category = HapticSuit)
		static void ResetPlugin();

	UFUNCTION(BlueprintCallable, Category = HapticSuit)
		static bool PlayHaptic(FString HapticEffectName, HapticFileType fileType, int32 Where = 16711935);

	UFUNCTION(BlueprintCallable, Category = HapticSuit)
		static bool PlayHapticSequenceOnAll(FString HapticEffectName);

	UFUNCTION(BlueprintCallable, Category = HapticSuit)
		static bool PlayHapticSequence(FString HapticEffectName, int32 Where);

	UFUNCTION(BlueprintCallable, Category = HapticSuit)
		static bool PlayHapticPattern(FString HapticEffectName);

	UFUNCTION(BlueprintCallable, Category = HapticSuit)
		static bool PlayHapticExperience(FString HapticEffectName);

	UFUNCTION(BlueprintCallable, Category = HapticSuit)
		static void ClearAllHaptics();
};


/**
*
*/
//UENUM(BlueprintType)		//"BlueprintType" is essential to include
//enum class HapticArea : uint8
//{
//	Forearm_Left	UMETA(DisplayName = "Forearm Left"),
//	Upper_Arm_Left	UMETA(DisplayName = "Upper Arm Left"),
//	Shoulder_Left	UMETA(DisplayName = "Shoulder Left"),
//	Back_Left		UMETA(DisplayName = "Back Left"),
//	Chest_Left		UMETA(DisplayName = "Chest Left"),
//	Upper_Ab_Left	UMETA(DisplayName = "Upper Ab Left"),
//	Mid_Ab_Left		UMETA(DisplayName = "Mid Ab Left"),
//	Lower_Ab_Left	UMETA(DisplayName = "Lower Ab Left"),
//
//	Forearm_Right	UMETA(DisplayName = "Forearm Right"),
//	Upper_Arm_Right	UMETA(DisplayName = "Upper Arm Right"),
//	Shoulder_Right	UMETA(DisplayName = "Shoulder Right"),
//	Back_Right		UMETA(DisplayName = "Back Right"),
//	Chest_Right 	UMETA(DisplayName = "Chest Right"),
//	Upper_Ab_Right 	UMETA(DisplayName = "Upper Ab Right"),
//	Mid_Ab_Right 	UMETA(DisplayName = "Mid Ab Right"),
//	Lower_Ab_Right 	UMETA(DisplayName = "Lower Ab Right")
//
//	/*Forearm_Left = 1	UMETA(DisplayName = "Forearm Left"),
//	Upper_Arm_Left = 2	UMETA(DisplayName = "Upper Arm Left"),
//	Shoulder_Left = 4	UMETA(DisplayName = "Shoulder Left"),
//	Back_Left = 8		UMETA(DisplayName = "Back Left"),
//	Chest_Left = 16		UMETA(DisplayName = "Chest Left"),
//	Upper_Ab_Left = 32	UMETA(DisplayName = "Upper Ab Left"),
//	Mid_Ab_Left = 64	UMETA(DisplayName = "Mid Ab Left"),
//	Lower_Ab_Left = 128	UMETA(DisplayName = "Lower Ab Left"),
//
//	Forearm_Right = 65536	UMETA(DisplayName = "Forearm Right"),
//	Upper_Arm_Right = 131072	UMETA(DisplayName = "Upper Arm Right"),
//	Shoulder_Right = 262144 	UMETA(DisplayName = "Shoulder Right"),
//	Back_Right = 524288		UMETA(DisplayName = "Back Right"),
//	Chest_Right = 1048576 	UMETA(DisplayName = "Chest Right"),
//	Upper_Ab_Right = 2097152 	UMETA(DisplayName = "Upper Ab Right"),
//	Mid_Ab_Right = 4194304	UMETA(DisplayName = "Mid Ab Right"),
//	Lower_Ab_Right = 8388608 	UMETA(DisplayName = "Lower Ab Right")*/
//
//	/*Forearm_Left = 1 << 0 		UMETA(DisplayName = "Forearm Left"),
//	Upper_Arm_Left = 1 << 1 	UMETA(DisplayName = "Upper Arm Left"),
//	Shoulder_Left = 1 << 2 		UMETA(DisplayName = "Shoulder Left"),
//	Back_Left = 1 << 3 			UMETA(DisplayName = "Back Left"),
//	Chest_Left = 1 << 4 		UMETA(DisplayName = "Chest Left"),
//	Upper_Ab_Left = 1 << 5 		UMETA(DisplayName = "Upper Ab Left"),
//	Mid_Ab_Left = 1 << 6 		UMETA(DisplayName = "Mid Ab Left"),
//	Lower_Ab_Left = 1 << 7		UMETA(DisplayName = "Lower Ab Left"),
//
//	Forearm_Right = 1 << 16 	UMETA(DisplayName = "Forearm Right"),
//	Upper_Arm_Right = 1 << 17 	UMETA(DisplayName = "Upper Arm Right"),
//	Shoulder_Right = 1 << 18 	UMETA(DisplayName = "Shoulder Right"),
//	Back_Right = 1 << 19 		UMETA(DisplayName = "Back Right"),
//	Chest_Right = 1 << 20 		UMETA(DisplayName = "Chest Right"),
//	Upper_Ab_Right = 1 << 21 	UMETA(DisplayName = "Upper Ab Right"),
//	Mid_Ab_Right = 1 << 22 		UMETA(DisplayName = "Mid Ab Right"),
//	Lower_Ab_Right = 1 << 23 	UMETA(DisplayName = "Lower Ab Right")*/
//};
