#include "HapticSuitPrivatePCH.h"

#include "UPlaybackHandleImpl.h"
#include "NSLoader.h"


void UPlaybackHandleImpl::Play()
{
	NSVR_PlaybackHandle_Command(m_handle, NSVR_PlaybackCommand::NSVR_PlaybackCommand_Play);
}

void UPlaybackHandleImpl::Pause()
{
	NSVR_PlaybackHandle_Command(m_handle, NSVR_PlaybackCommand::NSVR_PlaybackCommand_Pause);
}

void UPlaybackHandleImpl::Reset()
{
	NSVR_PlaybackHandle_Command(m_handle, NSVR_PlaybackCommand::NSVR_PlaybackCommand_Reset);
}

//On road to be implemented
float UPlaybackHandleImpl::ElapsedDuration()
{
	NSVR_EffectInfo info;
	NSVR_Result result = NSVR_PlaybackHandle_GetInfo(m_handle, &info);
	if (NSVR_SUCCESS(result))
	{
		return info.Elapsed;
	}
	UE_LOG(LogTemp, Error, TEXT("Failed PlaybackHandle GetInfo() Elapsed()\t\t ElapsedDuration() is returning -1.0 as a failure case (because we can't know the actual elapsed duration)"));

	return -1.0;
}

float UPlaybackHandleImpl::TotalDuration()
{
	NSVR_EffectInfo info;
	NSVR_Result result = NSVR_PlaybackHandle_GetInfo(m_handle, &info);
	if (NSVR_SUCCESS(result))
	{
		return info.Duration;
	}
	UE_LOG(LogTemp, Error, TEXT("Failed PlaybackHandle GetInfo() TotalDuration()\t\t TotalDuration() is returning -1.0 as a failure case (because we can't know the actual total duration)"));

	return -1.0;
}

bool UPlaybackHandleImpl::IsPlaying()
{
	NSVR_EffectInfo info;
	NSVR_Result result = NSVR_PlaybackHandle_GetInfo(m_handle, &info);
	if (NSVR_SUCCESS(result))
	{
		//This is a C enum, so you don't need the [NSVR_EffectInfo_State::], but it is there for readability
		return info.PlaybackState == NSVR_EffectInfo_State::NSVR_EffectInfo_State_Playing;
	}

	UE_LOG(LogTemp, Error, TEXT("Failed PlaybackHandle GetInfo()IsPlaying()\t\t IsPlaying() is returning false as a failure case (because we can't know if it is playing or not)"));
	return false;
}

bool UPlaybackHandleImpl::IsPaused()
{
	NSVR_EffectInfo info;
	NSVR_Result result = NSVR_PlaybackHandle_GetInfo(m_handle, &info);
	if (NSVR_SUCCESS(result))
	{
		//This is a C enum, so you don't need the [NSVR_EffectInfo_State::], but it is there for readability
		return info.PlaybackState == NSVR_EffectInfo_State::NSVR_EffectInfo_State_Paused;
	}

	UE_LOG(LogTemp, Error, TEXT("Failed PlaybackHandle GetInfo() IsPaused()\t\t IsPaused() is returning false as a failure case (because we can't know if it is paused or not)"));
	return false;
}

bool UPlaybackHandleImpl::IsFinished()
{
	NSVR_EffectInfo info;
	NSVR_Result result = NSVR_PlaybackHandle_GetInfo(m_handle, &info);
	if (NSVR_SUCCESS(result))
	{
		//This is a C enum, so you don't need the [NSVR_EffectInfo_State::], but it is there for readability
		bool isIdle = info.PlaybackState == (int)NSVR_EffectInfo_State::NSVR_EffectInfo_State_Idle;
		bool isDurationFinished = info.Elapsed >= info.Duration;

		return isIdle && isDurationFinished;
	}

	UE_LOG(LogTemp, Error, TEXT("Failed PlaybackHandle GetInfo() IsFinished()\t\t IsFinished() is returning false as a failure case (because we can't know if it is finished or not)"));

	return false;
}

UPlaybackHandleImpl::UPlaybackHandleImpl(NSVR_Timeline* timeline, NSVR_System* system)
{
	NSVR_PlaybackHandle_Create(&m_handle);
	NSVR_Timeline_Transmit(timeline, system, m_handle);
}

UPlaybackHandleImpl::~UPlaybackHandleImpl()
{
	NSVR_PlaybackHandle_Release(&m_handle);
}
