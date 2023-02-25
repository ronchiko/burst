#pragma once

#include <GLFW/glfw3.h>

#include <Burst/Common/Types/Notifier.h>
#include <Burst/Common/Utils/Monitor.h>

#include "../Events/IMonitorListener.h"

namespace burst::glfw {

	/**
	 * GLFW monitor info provider.
	 */
	class MonitorProvider : public monitor::IMonitorProvider,
							public IMonitorListener
	{
	public:
		MonitorProvider();

		/**
		 * Returns the resolution of a monitor by its index.
		 * 
		 * \param index
		 */
		Uint2 resolution(u32 index) const;

		virtual void on_monitor_event(GLFWmonitor *monitor, int event) override;

		GLFWmonitor *get_raw_primary_monitor() const;

	private:
		Vector<GLFWmonitor *> m_Monitors;
		Subscription m_glfwMonitorEventSubscription;
		u32 m_MainMonitor;
	};
}
