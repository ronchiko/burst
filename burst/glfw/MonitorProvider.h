#pragma once

#include <GLFW/glfw3.h>

#include <Burst/Common/Utils/Monitor.h>
#include <Burst/Common/Types/IToken.h>

namespace burst::glfw {

	/**
	 * GLFW monitor info provider.
	 */
	class MonitorProvider : public monitor::IMonitorProvider
	{
	public:
		MonitorProvider();

		Uint2 resolution(u32 index) const;

		void on_monitor_change(GLFWmonitor* monitor, int event);

		GLFWmonitor *get_raw_primary_monitor() const;

	private:
		Vector<GLFWmonitor *> m_Monitors;
		ITokenPtr m_Token;
		u32 m_MainMonitor;
	};
}
