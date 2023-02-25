#pragma once

#include <GLFW/glfw3.h>

#include <burst/common/Types/Notifier.h>

namespace burst::glfw {
	/**
	 * Callback interface for a monitor provider.
	 */
	class IMonitorListener
	{
	public:
		virtual ~IMonitorListener() = default;

		/**
		 * Invoked when a monitor is changed.
		 *
		 * \param monitor: The glfw monitor object that was changed
		 * \param event: The event id that was changed
		 */
		virtual void on_monitor_event(GLFWmonitor *monitor, int event) = 0;
	};

	inline Notifier<IMonitorListener> g_MonitorEvent = {};

	/**
	 * GLFW monitor event handler.
	 */
	inline void glfw_monitor_event(GLFWmonitor *monitor, int event)
	{
		g_MonitorEvent.notify(&IMonitorListener::on_monitor_event, monitor, event);
	}
}
