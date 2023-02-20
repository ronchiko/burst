#include "MonitorProvider.h"

#include <GLFW/glfw3.h>

#include <Burst/Common/Log.h>
#include <Burst/Common/Meta.h>
#include <Burst/Common/Types/Behavior/MemoryComparable.h>
#include <Burst/Common/Types/Notifier.h>
#include <Burst/Common/Types/SignalList.h>

#include "Error.h"


static burst::Notifier<burst::glfw::IMonitorProviderListener>
	g_MonitorCallbackList{};

/**
 * Finds the main monitor in a list of monitors.
 */
static burst::u32 find_main_monitor(const burst::Vector<GLFWmonitor *> monitors)
{
	using namespace burst;

	u32 index = 0;
	auto main = glfwGetPrimaryMonitor();

	auto iter = std::find(monitors.begin(), monitors.end(), main);
	if(monitors.end() == iter) {
		throw glfw::GlfwError("Failed to find primary monitor");
	}

	return static_cast<u32>(std::distance(monitors.begin(), iter));
}

namespace burst::glfw {

	/**
	 * The GLFW monitor event handler.
	 */
	static void monitor_event_handler(GLFWmonitor *monitor, int event)
	{
		g_MonitorCallbackList.notify(
			&IMonitorProviderListener::on_monitor_change, monitor, event);
	}

	/**
	 * Adds a new monitor event handler to monitor callback list, and initializes the
	 * callbacks if neccessary.
	 */
	static burst::Subscription
	add_monitor_provider(IMonitorProviderListener *listener)
	{
		static bool s_ActivatedCallback = false;
		if(!s_ActivatedCallback) {
			glfwSetMonitorCallback(monitor_event_handler);
		}

		return g_MonitorCallbackList.subscribe(listener);
	}

	/**
	 * Makes the monitors list.
	 */
	static Vector<GLFWmonitor *> make_monitors_list()
	{
		int monitors_count = 0;
		auto monitors = glfwGetMonitors(&monitors_count); // The buffer is owner
														  // by GLFW
		if(nullptr == monitors) {
			throw GlfwError("Failed to get monitors");
		}

		return Vector<GLFWmonitor *>(monitors, monitors + monitors_count);
	}

	MonitorProvider::MonitorProvider()
		: m_Monitors(make_monitors_list())
		, m_glfwMonitorEventSubscription(add_monitor_provider(this))
		, m_MainMonitor(find_main_monitor(m_Monitors))
	{}

	Uint2 MonitorProvider::resolution(u32 index) const
	{
		comapre_exchange(index, monitor::MAIN_MONITOR, m_MainMonitor);

		const auto *video = glfwGetVideoMode(m_Monitors[index]);
		ASSERT(video != nullptr, "Failed to get video mode");

		return { video->width, video->height };
	}

	void MonitorProvider::on_monitor_change(GLFWmonitor *monitor, int event)
	{
		if(GLFW_CONNECTED == event) {
			m_Monitors.push_back(monitor);
			return;
		}

		// Erase the provided monitor
		auto iter = std::find(m_Monitors.begin(), m_Monitors.end(), monitor);
		if(m_Monitors.end() == iter) {
			return;
		}

		m_Monitors.erase(iter);
		// Main monitor might be removed, should find it again
		m_MainMonitor = find_main_monitor(m_Monitors);
	}

	GLFWmonitor *MonitorProvider::get_raw_primary_monitor() const
	{
		return m_Monitors[m_MainMonitor];
	}
}
