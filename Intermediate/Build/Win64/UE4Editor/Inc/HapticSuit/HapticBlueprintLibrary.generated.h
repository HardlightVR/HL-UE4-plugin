// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	C++ class header boilerplate exported from UnrealHeaderTool.
	This is automatically generated by the tools.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

PRAGMA_DISABLE_DEPRECATION_WARNINGS
enum class HapticFileType : uint8;
#ifdef HAPTICSUIT_HapticBlueprintLibrary_generated_h
#error "HapticBlueprintLibrary.generated.h already included, missing '#pragma once' in HapticBlueprintLibrary.h"
#endif
#define HAPTICSUIT_HapticBlueprintLibrary_generated_h

#define HostProject_Plugins_HapticSuit_Source_HapticSuit_Classes_HapticBlueprintLibrary_h_29_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execClearAllHaptics) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UHapticBlueprintLibrary::ClearAllHaptics(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execPlayHapticExperience) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_HapticEffectName); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(bool*)Z_Param__Result=UHapticBlueprintLibrary::PlayHapticExperience(Z_Param_HapticEffectName); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execPlayHapticPattern) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_HapticEffectName); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(bool*)Z_Param__Result=UHapticBlueprintLibrary::PlayHapticPattern(Z_Param_HapticEffectName); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execPlayHapticSequence) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_HapticEffectName); \
		P_GET_PROPERTY(UIntProperty,Z_Param_Where); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(bool*)Z_Param__Result=UHapticBlueprintLibrary::PlayHapticSequence(Z_Param_HapticEffectName,Z_Param_Where); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execPlayHapticSequenceOnAll) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_HapticEffectName); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(bool*)Z_Param__Result=UHapticBlueprintLibrary::PlayHapticSequenceOnAll(Z_Param_HapticEffectName); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execPlayHaptic) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_HapticEffectName); \
		P_GET_ENUM(HapticFileType,Z_Param_fileType); \
		P_GET_PROPERTY(UIntProperty,Z_Param_Where); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(bool*)Z_Param__Result=UHapticBlueprintLibrary::PlayHaptic(Z_Param_HapticEffectName,HapticFileType(Z_Param_fileType),Z_Param_Where); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execResetPlugin) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UHapticBlueprintLibrary::ResetPlugin(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execPluginLoadedSuccessfully) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(bool*)Z_Param__Result=UHapticBlueprintLibrary::PluginLoadedSuccessfully(); \
		P_NATIVE_END; \
	}


#define HostProject_Plugins_HapticSuit_Source_HapticSuit_Classes_HapticBlueprintLibrary_h_29_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execClearAllHaptics) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UHapticBlueprintLibrary::ClearAllHaptics(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execPlayHapticExperience) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_HapticEffectName); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(bool*)Z_Param__Result=UHapticBlueprintLibrary::PlayHapticExperience(Z_Param_HapticEffectName); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execPlayHapticPattern) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_HapticEffectName); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(bool*)Z_Param__Result=UHapticBlueprintLibrary::PlayHapticPattern(Z_Param_HapticEffectName); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execPlayHapticSequence) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_HapticEffectName); \
		P_GET_PROPERTY(UIntProperty,Z_Param_Where); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(bool*)Z_Param__Result=UHapticBlueprintLibrary::PlayHapticSequence(Z_Param_HapticEffectName,Z_Param_Where); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execPlayHapticSequenceOnAll) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_HapticEffectName); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(bool*)Z_Param__Result=UHapticBlueprintLibrary::PlayHapticSequenceOnAll(Z_Param_HapticEffectName); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execPlayHaptic) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_HapticEffectName); \
		P_GET_ENUM(HapticFileType,Z_Param_fileType); \
		P_GET_PROPERTY(UIntProperty,Z_Param_Where); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(bool*)Z_Param__Result=UHapticBlueprintLibrary::PlayHaptic(Z_Param_HapticEffectName,HapticFileType(Z_Param_fileType),Z_Param_Where); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execResetPlugin) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UHapticBlueprintLibrary::ResetPlugin(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execPluginLoadedSuccessfully) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(bool*)Z_Param__Result=UHapticBlueprintLibrary::PluginLoadedSuccessfully(); \
		P_NATIVE_END; \
	}


#define HostProject_Plugins_HapticSuit_Source_HapticSuit_Classes_HapticBlueprintLibrary_h_29_INCLASS_NO_PURE_DECLS \
	private: \
	static void StaticRegisterNativesUHapticBlueprintLibrary(); \
	friend HAPTICSUIT_API class UClass* Z_Construct_UClass_UHapticBlueprintLibrary(); \
	public: \
	DECLARE_CLASS(UHapticBlueprintLibrary, UBlueprintFunctionLibrary, COMPILED_IN_FLAGS(0), 0, TEXT("/Script/HapticSuit"), NO_API) \
	DECLARE_SERIALIZER(UHapticBlueprintLibrary) \
	/** Indicates whether the class is compiled into the engine */ \
	enum {IsIntrinsic=COMPILED_IN_INTRINSIC};


#define HostProject_Plugins_HapticSuit_Source_HapticSuit_Classes_HapticBlueprintLibrary_h_29_INCLASS \
	private: \
	static void StaticRegisterNativesUHapticBlueprintLibrary(); \
	friend HAPTICSUIT_API class UClass* Z_Construct_UClass_UHapticBlueprintLibrary(); \
	public: \
	DECLARE_CLASS(UHapticBlueprintLibrary, UBlueprintFunctionLibrary, COMPILED_IN_FLAGS(0), 0, TEXT("/Script/HapticSuit"), NO_API) \
	DECLARE_SERIALIZER(UHapticBlueprintLibrary) \
	/** Indicates whether the class is compiled into the engine */ \
	enum {IsIntrinsic=COMPILED_IN_INTRINSIC};


#define HostProject_Plugins_HapticSuit_Source_HapticSuit_Classes_HapticBlueprintLibrary_h_29_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UHapticBlueprintLibrary(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UHapticBlueprintLibrary) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UHapticBlueprintLibrary); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UHapticBlueprintLibrary); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UHapticBlueprintLibrary(UHapticBlueprintLibrary&&); \
	NO_API UHapticBlueprintLibrary(const UHapticBlueprintLibrary&); \
public:


#define HostProject_Plugins_HapticSuit_Source_HapticSuit_Classes_HapticBlueprintLibrary_h_29_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UHapticBlueprintLibrary(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer) { }; \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UHapticBlueprintLibrary(UHapticBlueprintLibrary&&); \
	NO_API UHapticBlueprintLibrary(const UHapticBlueprintLibrary&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UHapticBlueprintLibrary); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UHapticBlueprintLibrary); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UHapticBlueprintLibrary)


#define HostProject_Plugins_HapticSuit_Source_HapticSuit_Classes_HapticBlueprintLibrary_h_29_PRIVATE_PROPERTY_OFFSET
#define HostProject_Plugins_HapticSuit_Source_HapticSuit_Classes_HapticBlueprintLibrary_h_26_PROLOG
#define HostProject_Plugins_HapticSuit_Source_HapticSuit_Classes_HapticBlueprintLibrary_h_29_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	HostProject_Plugins_HapticSuit_Source_HapticSuit_Classes_HapticBlueprintLibrary_h_29_PRIVATE_PROPERTY_OFFSET \
	HostProject_Plugins_HapticSuit_Source_HapticSuit_Classes_HapticBlueprintLibrary_h_29_RPC_WRAPPERS \
	HostProject_Plugins_HapticSuit_Source_HapticSuit_Classes_HapticBlueprintLibrary_h_29_INCLASS \
	HostProject_Plugins_HapticSuit_Source_HapticSuit_Classes_HapticBlueprintLibrary_h_29_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define HostProject_Plugins_HapticSuit_Source_HapticSuit_Classes_HapticBlueprintLibrary_h_29_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	HostProject_Plugins_HapticSuit_Source_HapticSuit_Classes_HapticBlueprintLibrary_h_29_PRIVATE_PROPERTY_OFFSET \
	HostProject_Plugins_HapticSuit_Source_HapticSuit_Classes_HapticBlueprintLibrary_h_29_RPC_WRAPPERS_NO_PURE_DECLS \
	HostProject_Plugins_HapticSuit_Source_HapticSuit_Classes_HapticBlueprintLibrary_h_29_INCLASS_NO_PURE_DECLS \
	HostProject_Plugins_HapticSuit_Source_HapticSuit_Classes_HapticBlueprintLibrary_h_29_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID HostProject_Plugins_HapticSuit_Source_HapticSuit_Classes_HapticBlueprintLibrary_h


#define FOREACH_ENUM_HAPTICFILETYPE(op) \
	op(HapticFileType::Sequence) \
	op(HapticFileType::SequenceOnAll) \
	op(HapticFileType::Pattern) \
	op(HapticFileType::Experience) 
PRAGMA_ENABLE_DEPRECATION_WARNINGS