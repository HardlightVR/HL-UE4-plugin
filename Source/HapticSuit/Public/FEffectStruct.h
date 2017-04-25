// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once
#include "CoreMinimal.h"

#include "UObject/ObjectMacros.h"
#include "UObject/Object.h"
#include "FEffectStruct.generated.h"
UENUM(BlueprintType)
enum class EEffects : uint8{
	Bump = 1 UMETA(DisplayName = "Bump"),
	Buzz = 2 UMETA(DisplayName = "Buzz"),
	Click = 3 UMETA(DisplayName = "Click"),
	Double_Click = 4 UMETA(DisplayName = "Double Click"),

	Fuzz = 5 UMETA(DisplayName = "Fuzz"),
	Hum = 6 UMETA(DisplayName = "Hum"),
	Pulse = 8 UMETA(DisplayName = "Pulse"),
	Tick = 11 UMETA(DisplayName = "Tick") ,
	Triple_Click = 16 UMETA(DisplayName = "Triple Click")
};

USTRUCT()
struct HAPTICSUIT_API FEffectStruct
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditAnywhere, Category = Data)
	float Time;

	UPROPERTY(EditAnywhere, Category = Data)
	float Duration;
	
	UPROPERTY(EditAnywhere, Category = Data)
	float Strength;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	EEffects Effect;

	FEffectStruct(double time, double duration, double strength, EEffects effect);
	FEffectStruct();

};