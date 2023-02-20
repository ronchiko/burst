#pragma once

#include <GLFW/glfw3.h>

#include <Burst/Common/Types/Notifier.h>
#include <Burst/Common/Utils/Monitor.h>

namespace burst::glfw {

	/**
	 * Callback interface for a monitor provider.
	 */
	class IMonitorProviderListener
	{
	public:
		virtual ~IMonitorProviderListener() = default;

		/**
		 * Invoked when a monitor is changed.
		 *
		 * \param monitor: The glfw monitor object that was changed
		 * \param event: The event id that was changed
		 */
		virtual void on_monitor_change(GLFWmonitor *monitor, int event) = 0;
	};

	/**
	 * GLFW monitor info provider.
	 */
	class MonitorProvider : public monitor::IMonitorProvider,
							public IMonitorProviderListener
	{
	public:
		MonitorProvider();

		/**
		 * Returns the resolution of a monitor by its index.
		 * 
		 * \param index
		 */
		Uint2 resolution(u32 index) const;

		virtual void on_monitor_change(GLFWmonitor *monitor, int event) override;

		GLFWmonitor *get_raw_primary_monitor() const;

	private:
		Vector<GLFWmonitor *> m_Monitors;
		Subscription m_glfwMonitorEventSubscription;
		u32 m_MainMonitor;
	};
}
