// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once


#include "PlatformFilemanager.h"
#include "GenericPlatformFile.h"
#include "Developer/AssetTools/Public/AssetTypeActions_Base.h"
#include "Runtime/Engine/Classes/EditorFramework/ThumbnailInfo.h"
class FHapticTypeActions : public FAssetTypeActions_Base
{
public:

	virtual FText GetName() const override;
	virtual FColor GetTypeColor() const override;
	virtual UClass* GetSupportedClass() const override;
	virtual uint32 GetCategories() override;
	virtual UThumbnailInfo* GetThumbnailInfo(UObject * Asset) const override;

};