#pragma once
#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "UObject/Object.h"

UENUM(BlueprintType, Meta = (Bitflags))
enum class EAreaFlags : uint8 {
	/*Forearm_Left = 1 UMETA(DisplayName = "Forearm Left"),
	Upper_Arm_Left = 2 UMETA(DisplayName = "Upper Arm Left"),
	Shoulder_Left = 3 UMETA(DisplayName = "Shoulder Left"),
	Back_Left = 4 UMETA(DisplayName = "Back Left"),
	Chest_Left = 5 UMETA(DisplayName = "Chest Left"),
	Upper_Ab_Left = 6 UMETA(DisplayName = "Upper Ab Left"),
	Mid_Ab_Left = 7 UMETA(DisplayName = "Mid Ab Left"),
	Lower_Ab_Left = 8 UMETA(DisplayName = "Lower Ab Left"),

	Forearm_Right = 17 UMETA(DisplayName = "Forearm Right"),
	Upper_Arm_Right = 18 UMETA(DisplayName = "Upper Arm Right"),
	Shoulder_Right = 19 UMETA(DisplayName = "Shoulder Right"),
	Back_Right = 20 UMETA(DisplayName = "Back Right"),
	Chest_Right = 21 UMETA(DisplayName = "Chest Right"),
	Upper_Ab_Right = 22 UMETA(DisplayName = "Upper Ab Right"),
	Mid_Ab_Right = 23 UMETA(DisplayName = "Mid Ab Right"),
	Lower_Ab_Right = 24 UMETA(DisplayName = "Lower Ab Right")*/

	Forearm_Left = 0 UMETA(DisplayName = "Forearm Left"),
	Upper_Arm_Left = 1 UMETA(DisplayName = "Upper Arm Left"),
	Shoulder_Left = 2 UMETA(DisplayName = "Shoulder Left"),
	Back_Left = 3 UMETA(DisplayName = "Back Left"),
	Chest_Left = 4 UMETA(DisplayName = "Chest Left"),
	Upper_Ab_Left = 5 UMETA(DisplayName = "Upper Ab Left"),
	Mid_Ab_Left = 6 UMETA(DisplayName = "Mid Ab Left"),
	Lower_Ab_Left = 7 UMETA(DisplayName = "Lower Ab Left"),

	Forearm_Right = 16 UMETA(DisplayName = "Forearm Right"),
	Upper_Arm_Right = 17 UMETA(DisplayName = "Upper Arm Right"),
	Shoulder_Right = 18 UMETA(DisplayName = "Shoulder Right"),
	Back_Right = 19 UMETA(DisplayName = "Back Right"),
	Chest_Right = 20 UMETA(DisplayName = "Chest Right"),
	Upper_Ab_Right = 21 UMETA(DisplayName = "Upper Ab Right"),
	Mid_Ab_Right = 22 UMETA(DisplayName = "Mid Ab Right"),
	Lower_Ab_Right = 23 UMETA(DisplayName = "Lower Ab Right")
};
