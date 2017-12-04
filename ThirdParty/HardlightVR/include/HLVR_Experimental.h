/*! \file HLVR_Experimental.h
	\brief Experimental and unstable features
	\copyright Copyright 2017 NullSpace VR, Inc All Rights reserved.
*/
#pragma once


#include <stdint.h>
#include "HLVR_Forwards.h"
#include "HLVR_Errors.h"


#ifdef HLVR_EXPORTS
#define HLVR_EXPERIMENTAL_API __declspec(dllexport) 
#else
#define HLVR_EXPERIMENTAL_API __declspec(dllimport) 
#endif

#define HLVR_RETURN_EXP(ReturnType) HLVR_EXPERIMENTAL_API ReturnType __cdecl

#ifdef __cplusplus
extern "C" {
#endif

	/* Note: 
	*	
	*	Functions and data structures in this header file are subject to breaking changes within minor API upgrades.
	*/


	typedef struct HLVR_BodyView HLVR_BodyView;


	/*! thing*/
	HLVR_RETURN_EXP(HLVR_Result) HLVR_BodyView_Create(HLVR_BodyView** body);
	HLVR_RETURN_EXP(HLVR_Result) HLVR_BodyView_Release(HLVR_BodyView** body);
	HLVR_RETURN_EXP(HLVR_Result) HLVR_BodyView_Poll(HLVR_BodyView* body, HLVR_System* system);
	HLVR_RETURN_EXP(HLVR_Result) HLVR_BodyView_GetNodeCount(HLVR_BodyView* body, uint32_t* outNodeCount);
	HLVR_RETURN_EXP(HLVR_Result) HLVR_BodyView_GetNodeType(HLVR_BodyView * body, uint32_t nodeIndex, uint32_t* outType);
	HLVR_RETURN_EXP(HLVR_Result) HLVR_BodyView_GetNodeRegion(HLVR_BodyView * body, uint32_t nodeIndex, uint32_t* outRegion);

	HLVR_RETURN_EXP(HLVR_Result) HLVR_BodyView_GetIntensity(HLVR_BodyView * body, uint32_t nodeIndex, float* outIntensity);

	
	typedef struct HLVR_Quaternion {
		float w;
		float x;
		float y;
		float z;
	} HLVR_Quaternion;

	typedef struct HLVR_Vector3f {
		float x;
		float y;
		float z;
	} HLVR_Vector3f;

	typedef struct HLVR_TrackingUpdate {
		HLVR_Quaternion chest;
		HLVR_Quaternion left_upper_arm;
		HLVR_Quaternion left_forearm;
		HLVR_Quaternion right_upper_arm;
		HLVR_Quaternion right_forearm;

		HLVR_Vector3f chest_gravity;
		HLVR_Vector3f chest_compass;

		HLVR_Vector3f left_upper_arm_gravity;
		HLVR_Vector3f left_upper_arm_compass;

		HLVR_Vector3f left_forearm_gravity;
		HLVR_Vector3f left_forearm_compass;

		HLVR_Vector3f right_upper_arm_gravity;
		HLVR_Vector3f right_upper_arm_compass;

		HLVR_Vector3f right_forearm_gravity;
		HLVR_Vector3f right_forearm_compass;
	} HLVR_TrackingUpdate;

	
	HLVR_RETURN_EXP(HLVR_Result) HLVR_System_PollTracking(HLVR_System* ptr, HLVR_TrackingUpdate* updatePtr);
	HLVR_RETURN_EXP(HLVR_Result) HLVR_System_EnableTracking(HLVR_System* ptr, uint32_t device_id);
	HLVR_RETURN_EXP(HLVR_Result) HLVR_System_DisableTracking(HLVR_System* ptr, uint32_t device_id);

	HLVR_RETURN_EXP(HLVR_Result) HLVR_System_StreamEvent(HLVR_System* system, HLVR_Event* data);

	

#ifdef __cplusplus
}
#endif

