#pragma once


#ifdef NSLOADER_EXPORTS
#define NSLOADER_API __declspec(dllexport) 
#else
#define NSLOADER_API __declspec(dllimport) 
#endif


struct _NSVRPlugin;
typedef struct _NSVRPlugin* NSVRPlugin;


namespace NullSpaceDLL {
	struct Quaternion {
		float w;
		float x;
		float y;
		float z;
	};
	struct InteropTrackingUpdate {
		Quaternion chest;
		Quaternion left_upper_arm;
		Quaternion left_forearm;
		Quaternion right_upper_arm;
		Quaternion right_forearm;
	};

	enum Command
	{
		PLAY = 0, PAUSE, RESET, RELEASE
	};
	enum EngineCommand
	{
		PLAY_ALL = 1, PAUSE_ALL, CLEAR_ALL, ENABLE_TRACKING, DISABLE_TRACKING
	};

	enum SuitStatus
	{
		Disconnected = 0,
		Connected = 2
	};

	enum FileType {
		Sequence,
		Pattern,
		Experience
	};
	enum AreaFlag
	{
		None,
		Forearm_Left = 1 << 0,
		Upper_Arm_Left = 1 << 1,
		Shoulder_Left = 1 << 2,
		Back_Left = 1 << 3,
		Chest_Left = 1 << 4,
		Upper_Ab_Left = 1 << 5,
		Mid_Ab_Left = 1 << 6,
		Lower_Ab_Left = 1 << 7,

		Forearm_Right = 1 << 16,
		Upper_Arm_Right = 1 << 17,
		Shoulder_Right = 1 << 18,
		Back_Right = 1 << 19,
		Chest_Right = 1 << 20,
		Upper_Ab_Right = 1 << 21,
		Mid_Ab_Right = 1 << 22,
		Lower_Ab_Right = 1 << 23,
		Forearm_Both = Forearm_Left | Forearm_Right,
		Upper_Arm_Both = Upper_Arm_Left | Upper_Arm_Right,
		Shoulder_Both = Shoulder_Left | Shoulder_Right,
		Back_Both = Back_Left | Back_Right,
		Chest_Both = Chest_Left | Chest_Right,
		Upper_Ab_Both = Upper_Ab_Left | Upper_Ab_Right,
		Mid_Ab_Both = Mid_Ab_Left | Mid_Ab_Right,
		Lower_Ab_Both = Lower_Ab_Left | Lower_Ab_Right,
		Left_All = 0x000000FF,
		Right_All = 0x00FF0000,
		All_Areas = Left_All | Right_All,
	};

}

extern "C" {
	

	NSLOADER_API NSVRPlugin __stdcall NSVR_Create();
	
	NSLOADER_API unsigned int __stdcall NSVR_GenHandle(NSVRPlugin ptr);
	NSLOADER_API int  __stdcall NSVR_PollStatus(NSVRPlugin ptr);
	NSLOADER_API void __stdcall NSVR_PollTracking(NSVRPlugin ptr, NullSpaceDLL::InteropTrackingUpdate& q);
	NSLOADER_API void __stdcall NSVR_Delete(NSVRPlugin ptr);
	NSLOADER_API bool __stdcall NSVR_CreateSequence(NSVRPlugin ptr, unsigned int handle, LPSTR name, unsigned int loc);
	NSLOADER_API bool __stdcall NSVR_Load(NSVRPlugin ptr, LPSTR param, int fileType);

	NSLOADER_API bool __stdcall NSVR_CreatePattern(NSVRPlugin ptr, unsigned int handle, LPSTR name);

	NSLOADER_API bool __stdcall NSVR_CreateExperience(NSVRPlugin ptr, unsigned int handle, LPSTR name);

	NSLOADER_API void __stdcall NSVR_HandleCommand(NSVRPlugin ptr, unsigned int handle, short command);

	NSLOADER_API char* __stdcall NSVR_GetError(NSVRPlugin ptr);

	NSLOADER_API void __stdcall NSVR_FreeString(char* string);

	NSLOADER_API bool __stdcall NSVR_EngineCommand(NSVRPlugin ptr, short command);

	NSLOADER_API bool __stdcall NSVR_InitializeFromFilesystem(NSVRPlugin ptr, LPSTR path);

}