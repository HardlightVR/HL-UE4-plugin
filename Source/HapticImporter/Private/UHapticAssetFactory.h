// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "PlatformFilemanager.h"
#include "GenericPlatformFile.h"
#include "Editor/UnrealEd/Classes/Factories/Factory.h"
#include "HapticAssetImporter.h"
#include "UHapticAssetFactory.generated.h"

UCLASS()
class UHapticAssetFactory : public UFactory
{
	GENERATED_UCLASS_BODY()
		
//	virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
	virtual UObject* FactoryCreateFile(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, const FString& FileName, const TCHAR* Parms, FFeedbackContext* Warn, bool& bOutOperationCanceled) override;
	virtual UObject* FactoryCreateText(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, const TCHAR* Type, const TCHAR*& Buffer, const TCHAR* BufferEnd, FFeedbackContext* Warn) override;


	virtual bool FactoryCanImport(const FString& Filename) override;

private:
	FHapticAssetImporter Importer;

};