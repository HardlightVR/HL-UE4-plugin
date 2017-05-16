// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "PlatformFilemanager.h"
#include "GenericPlatformFile.h"
#include "Editor/UnrealEd/Classes/Factories/Factory.h"
#include "UHapticExperienceFactory.generated.h"

UCLASS()
class UHapticExperienceFactory : public UFactory
{
	GENERATED_UCLASS_BODY()


	virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;

};