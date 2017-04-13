// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "HapticImporterPrivatePCH.h"
#include "UHapticAssetFactory.h"
#include "UHapticAsset.h"
#include "Runtime/Core/Public/GenericPlatform/GenericPlatformFile.h"
#include "Runtime/Core/Public/Misc/FileHelper.h"
#include "HapticAssetImporter.h"
#include "Json.h"
#include "Editor/UnrealEd/Public/Editor.h"
#include "Runtime/Core/Public/GenericPlatform/GenericPlatformProcess.h"


UHapticAssetFactory::UHapticAssetFactory(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	bCreateNew = true;
	bEditAfterNew = true;
	bText = true;
//	ImportPriority = 999999999;
	SupportedClass = UHapticAsset::StaticClass();
	Formats.Add(TEXT("hdf;Haptic Description File"));
	Formats.Add(TEXT("json;Haptic Description File"));
	bEditorImport = true;
	bCreateNew = false;


}

//
//UObject* UHapticAssetFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
//{
//	IPlatformFile& PlatformFile = IPlatformFile::GetPlatformPhysical();
//	FString MyFileName = FString(TEXT("C:/Users/NullSpace Team/Documents/testseq.hdf"));
//	const TCHAR* MyTCharFileName = *MyFileName;
//	IFileHandle* File = PlatformFile.OpenRead(MyTCharFileName);
//	FString JsonRaw;
//	if (!FFileHelper::LoadFileToString(JsonRaw, MyTCharFileName)) {
//		UE_LOG(LogTemp, Warning, TEXT("Unable to import the bump sequence"));
//		return nullptr;
//	}
//	
//	UE_LOG(LogTemp, Warning, TEXT("Successfully imported the result!"));
//
//	
//	if (Importer.ImportFromString(JsonRaw, MyFileName)) {
//		UHapticAsset* HapticAsset = NewObject<UHapticAsset>(InParent, Name, Flags);
//		if (!Importer.PerformImport(InParent, Name, Flags, HapticAsset))
//		{
//
//			UE_LOG(LogTemp, Warning, TEXT("Couldnt do step PerformImport"));
//
//
//		}
//		return HapticAsset;
//	}
//	
//	return nullptr;
//}

UObject* UHapticAssetFactory::FactoryCreateFile(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, const FString& FileName, const TCHAR* Parms, FFeedbackContext* Warn, bool& bOutOperationCanceled)
{

	IPlatformFile& PlatformFile = IPlatformFile::GetPlatformPhysical();
	const TCHAR* MyTCharFileName = *FileName;
	FString JsonRaw;
	if (!FFileHelper::LoadFileToString(JsonRaw, MyTCharFileName)) {
		UE_LOG(LogTemp, Warning, TEXT("Unable to import the bump sequence"));
		return nullptr;
	}

	UObject* Result = nullptr;
	if (Importer.ImportFromString(JsonRaw, FileName)) {
		UHapticAsset* HapticAsset = nullptr;
		if (!Importer.PerformImport(InParent,Name,  Flags, &HapticAsset))
		{
			
			UE_LOG(LogTemp, Warning, TEXT("Couldnt do step PerformImport"));

			
		}
		HapticAsset->PopulateDataFromJson();
		Result = HapticAsset;
	}
	 
	Importer = FHapticAssetImporter();
	return Result;
}



UObject * UHapticAssetFactory::FactoryCreateText(UClass * InClass, UObject * InParent, FName InName, EObjectFlags Flags, UObject * Context, const TCHAR * Type, const TCHAR *& Buffer, const TCHAR * BufferEnd, FFeedbackContext * Warn)
{
	Flags |= RF_Transactional;
	FEditorDelegates::OnAssetPreImport.Broadcast(this, InClass, InParent, InName, Type);


//	FAssetToolsModule& AssetToolsModule = FModuleManager::GetModuleChecked<FAssetToolsModule>("AssetTools");

	const FString FactoryCurrentFilename = UFactory::GetCurrentFilename();
	
	FString CurrentSourcePath;
	FString FilenameNoExtension;
	FString UnusedExtension;
	FPaths::Split(FactoryCurrentFilename, CurrentSourcePath, FilenameNoExtension, UnusedExtension);


	const FString NameForErrors(InName.ToString());
	const FString FileContent(BufferEnd - Buffer, Buffer);
	UObject* Result = nullptr;
	if (Importer.ImportFromString(FileContent, NameForErrors))
	{
		UHapticAsset* HapticAsset = nullptr;
		if (!Importer.PerformImport(InParent, InName, Flags, &HapticAsset))
		{

			UE_LOG(LogTemp, Warning, TEXT("Couldnt do step PerformImport"));


		}
		HapticAsset->PopulateDataFromJson();
		FEditorDelegates::OnAssetPostImport.Broadcast(this, HapticAsset);

		Result = HapticAsset;
	}

	Importer = FHapticAssetImporter();
	return Result;

}

bool UHapticAssetFactory::FactoryCanImport(const FString& Filename)
{
	FString FileContent;
	if (FFileHelper::LoadFileToString(/*out*/ FileContent, *Filename))
	{
		return FHapticAssetImporter::CanImportJSON(FileContent);
	}

	return false;
}

