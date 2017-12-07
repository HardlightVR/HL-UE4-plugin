#pragma once

#include "HLVR_Errors.h"

namespace hlvr 
{



inline const char* error_c_str(HLVR_Result result) {
	switch (result) {
	case HLVR_Error_UNKNOWN:
		return "Unknown";
	case HLVR_Error_Unspecified:
		return "Unspecified";
	case HLVR_Error_NullArgument:
		return "NullArgument";
	case HLVR_Error_InvalidArgument:
		return "InvalidArgument";
	case HLVR_Error_InvalidEventType:
		return "InvalidEventType";
	case HLVR_Error_NotConnected:
		return "NotConnected";
	case HLVR_Error_NoSuchHandle:
		return "NoSuchHandle";
	case HLVR_Error_NoMoreDevices:
		return "NoMoreDevices";
	case HLVR_Error_NoMoreNodes:
		return "NoMoreNodes";
	case HLVR_Error_InvalidTimeOffset:
		return "InvalidTimeOffset";
	case HLVR_Error_EmptyTimeline:
		return "EmptyTimeline";
	default:
		return "Unknown";
	}
}

class status_code {
public:
	explicit status_code(HLVR_Result result) : m_code{ result } {}
	status_code() = default;
	const char* what() const {
		return error_c_str(m_code);
	}
	const HLVR_Result value() const {
		return m_code;
	}
	explicit operator bool() const{
		return HLVR_OK(m_code);
	}
private:
	HLVR_Result m_code;
};


}