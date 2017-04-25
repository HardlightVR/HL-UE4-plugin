// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "HapticSuitPrivatePCH.h"
#include "HapticSuit.h"
#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

#include "Runtime/Core/Public/Misc/Paths.h"
#include "nsloader.h"
#include <string>

using namespace NullSpaceDLL;

#define LOCTEXT_NAMESPACE "FHapticSuitModule"
//DEFINE_LOG_CATEGORY(LogHapticPlugin);

void FHapticSuitModule::StartupModule()
{
	UE_LOG(LogTemp, Warning, TEXT("Startup Module for NSVR Plugin"));
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Startup HapticSuit Plugin"));

	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	Plugin = NSVR_Create();
	//ensureMsgf(Plugin != nullptr, TEXT("NSVR Plugin failed to successfully create. This should never occur."));
	//NSVR_InitializeFromFilesystem(Plugin, "C:/Haptics");
	
	InitializeIfValidHapticDirectory();
}

void FHapticSuitModule::ShutdownModule()
{
	UE_LOG(LogTemp, Warning, TEXT("Shutdown Module for NSVR Plugin"));
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	NSVR_Delete(Plugin);
}

void FHapticSuitModule::InitializeIfValidHapticDirectory()
{
	FString contentPath = FPaths::ConvertRelativePathToFull(FPaths::GameContentDir()) + TEXT("Haptics/");

	bool result = VerifyOrCreateDirectory(contentPath);

	if (result)
	{
		UE_LOG(LogTemp, Warning, TEXT("Successfully found or created the Haptics Content Directory"), *contentPath);
		std::string contentPathStr(TCHAR_TO_UTF8(*contentPath));
		UE_LOG(LogTemp, Warning, TEXT("%s"), *contentPath);
		char* lpStr = const_cast<char *>(contentPathStr.c_str());
		NSVR_InitializeFromFilesystem(Plugin, lpStr);
	}
	/*if (FPaths::DirectoryExists(contentPath))
	{
		std::string contentPathStr(TCHAR_TO_UTF8(*contentPath));
		UE_LOG(LogTemp, Warning, TEXT("%s"), *contentPath);
		char* lpStr = const_cast<char *>(contentPathStr.c_str());
		NSVR_InitializeFromFilesystem(Plugin, lpStr);
	}*/
}

bool FHapticSuitModule::PluginLoadedSuccessfully()
{
	return (Plugin != nullptr);
}

void FHapticSuitModule::ResetPlugin()
{
	UE_LOG(LogTemp, Warning, TEXT("Resetting the NSVR Plugin"));
	ClearAllHaptics();
	NSVR_Delete(Plugin);
	Plugin = NSVR_Create();

	//NSVR_InitializeFromFilesystem(Plugin, "C:/Haptics");

	InitializeIfValidHapticDirectory();
}

bool FHapticSuitModule::LoadAndPlaySequenceOnAll(FString SequenceName)
{
	return LoadAndPlaySequence(SequenceName, (int32)AreaFlag::All_Areas);
}

bool FHapticSuitModule::LoadAndPlaySequence(FString SequenceName, int32 Where)
{
	bool loadedSuccessfully = NSVR_Load(Plugin, TCHAR_TO_ANSI(*SequenceName), FileType::Sequence);

	//ensureMsgf(loadedSuccessfully, TEXT("Sequence [%s] loaded unsuccessfully: Check namespace, file name & JSON file contents"), SequenceName);
	if (!loadedSuccessfully)
	{
		UE_LOG(LogTemp, Warning, TEXT("Sequence loaded unsuccessfully: Check namespace, file name & JSON file contents"));
		return false;
	}
	//Generate a unique handle for use with this sequence
	unsigned int handle = NSVR_GenHandle(Plugin);
	//Communicate with the service to actually create the effect with the given handle
	bool createdSuccessfully = NSVR_CreateSequence(Plugin, handle, TCHAR_TO_ANSI(*SequenceName), (AreaFlag)Where);

	//ensureMsgf(createdSuccessfully, TEXT("Sequence [%s] was loaded successfully but failed to create handle. Contact NullSpace VR's Software Team."), SequenceName);
	if (!createdSuccessfully)
		return false;

	NSVR_HandleCommand(Plugin, handle, Command::PLAY);
	return true;
}

bool FHapticSuitModule::LoadAndPlayExperience(FString ExperienceName)
{
	bool loadedSuccessfully = NSVR_Load(Plugin, TCHAR_TO_ANSI(*ExperienceName), FileType::Experience);

	if (!loadedSuccessfully)
	{
		UE_LOG(LogTemp, Warning, TEXT("Experience loaded unsuccessfully: Check namespace, file name & JSON file contents"));
		return false;
	}

	//Generate a unique handle for use with this sequence
	unsigned int handle = NSVR_GenHandle(Plugin);
	//Communicate with the service to actually create the effect with the given handle
	bool createdSuccessfully = NSVR_CreateExperience(Plugin, handle, TCHAR_TO_ANSI(*ExperienceName));
	//ensureMsgf(createdSuccessfully, TEXT("Sequence [%s] was loaded successfully but failed to create handle. Contact NullSpace VR's Software Team."), ExperienceName);
	if (!createdSuccessfully)
		return false;

	//Now play the effect!
	NSVR_HandleCommand(Plugin, handle, Command::PLAY);
	return true;
}

bool FHapticSuitModule::LoadAndPlayPattern(FString PatternName)
{
	bool loadedSuccessfully = NSVR_Load(Plugin, TCHAR_TO_ANSI(*PatternName), FileType::Pattern);

	//UE_LOG(LogHapticPlugin, Log, TEXT(“Pattern [%s] loaded unsuccessfully: Check namespace, file & JSON file contents”), *PatternName);

	if (!loadedSuccessfully)
	{
		UE_LOG(LogTemp, Warning, TEXT("Pattern loaded unsuccessfully: Check namespace, file name & JSON file contents"));
		return false;
	}

	//Generate a unique handle for use with this sequence
	unsigned int handle = NSVR_GenHandle(Plugin);
	//Communicate with the service to actually create the effect with the given handle
	bool createdSuccessfully = NSVR_CreatePattern(Plugin, handle, TCHAR_TO_ANSI(*PatternName));

	//ensureMsgf(createdSuccessfully, TEXT("Sequence [%s] was loaded successfully but failed to create handle. Contact NullSpace VR's Software Team."), PatternName);
	if (!createdSuccessfully)
		return false;

	//Now play the effect!
	NSVR_HandleCommand(Plugin, handle, Command::PLAY);
	return true;
}

void FHapticSuitModule::ClearAllHaptics()
{
	NSVR_EngineCommand(Plugin, EngineCommand::CLEAR_ALL);
}



#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FHapticSuitModule, HapticSuit)