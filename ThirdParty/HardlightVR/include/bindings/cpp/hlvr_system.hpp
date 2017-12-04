#pragma once

#include <vector>
#include "HLVR.h"
#include "HLVR_Experimental.h"
#include "detail/hlvr_native_handle_owner.hpp"
#include "hlvr_event.hpp"
#include "hlvr_error.hpp"

#include <cassert>

namespace hlvr {

namespace detail {

	using system_traits = native_traits<HLVR_System, decltype(&HLVR_System_Create), decltype(&HLVR_System_Destroy)>;

}

struct nodes_t {};
struct regions_t {};

const static nodes_t nodes{};
const static regions_t regions{};



class system : public detail::native_handle_owner<system, detail::system_traits> {
public:
	using system_handle = detail::native_handle_owner<system, detail::system_traits>;

	system() : system_handle(&HLVR_System_Destroy) {}
	void shutdown() {
		m_handle.reset(nullptr);
	}

	expected<HLVR_RuntimeInfo, status_code> get_runtime_info() const {
		assert(m_handle);
		HLVR_RuntimeInfo info = { 0 };
		auto ec = HLVR_System_GetRuntimeInfo(m_handle.get(), &info);
		if (HLVR_OK(ec)) {
			return info;
		}
		else {
			return make_unexpected(status_code(ec));
		}
	}

	std::vector<HLVR_DeviceInfo> get_known_devices() {
		assert(m_handle);

		std::vector<HLVR_DeviceInfo> devices;

		HLVR_DeviceIterator iter;
		HLVR_DeviceIterator_Init(&iter);

		while (HLVR_OK(HLVR_DeviceIterator_Next(&iter, m_handle.get()))) {
			devices.push_back(iter.DeviceInfo);
		}

		return devices;
	}

	std::vector<HLVR_NodeInfo> get_nodes(uint32_t device_id) {
		assert(m_handle);

		std::vector<HLVR_NodeInfo> nodes;

		HLVR_NodeIterator iter;
		HLVR_NodeIterator_Init(&iter);

		while (HLVR_OK(HLVR_NodeIterator_Next(&iter, device_id, m_handle.get()))) {
			nodes.push_back(iter.NodeInfo);
		}

		return nodes;
	}

	std::vector<HLVR_NodeInfo> get_all_nodes() {
		return get_nodes(hlvr_allnodes);
	}

	status_code push_event(hlvr::event& event) {
		assert(m_handle);
		assert(event);
		return status_code(HLVR_System_StreamEvent(m_handle.get(), event.native_handle()));
	}


	expected<HLVR_TrackingUpdate, status_code> poll_tracking() {
		assert(m_handle);
		HLVR_TrackingUpdate update = { 0 };
		auto ec = HLVR_System_PollTracking(m_handle.get(), &update);
		if (HLVR_OK(ec)) { 
			return update; 
		} else { 
			return make_unexpected(status_code(ec));
		}
	}

	status_code enable_tracking(uint32_t device_id) {
		assert(m_handle);
		return status_code(HLVR_System_EnableTracking(m_handle.get(), device_id));
	}

	status_code disable_tracking(uint32_t device_id) {
		assert(m_handle);
		return status_code(HLVR_System_DisableTracking(m_handle.get(), device_id));
	}

	
	static expected<system, status_code> make() {
		return make_helper(&HLVR_System_Create);
	}

	status_code suspend_all_haptics() {
		assert(m_handle);
		return status_code( HLVR_System_SuspendEffects(m_handle.get()));
	}

	status_code resume_all_haptics() {
		assert(m_handle);
		return status_code(HLVR_System_ResumeEffects(m_handle.get()));
	}

	status_code cancel_all_haptics() {
		assert(m_handle);
		return status_code(HLVR_System_CancelEffects(m_handle.get()));
	}

private:
	friend class system_handle;
	explicit system(HLVR_System* handle) : system_handle( handle, &HLVR_System_Destroy ) {}
};


}