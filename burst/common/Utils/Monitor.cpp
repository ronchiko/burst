#include "Utils/Monitor.h"

#include "Log.h"

namespace burst::monitor {

	static Shared<IMonitorProvider> g_Provider = nullptr;

	void set_provider(Shared<IMonitorProvider> provider)
	{
		g_Provider = provider;
	}

	Uint2 resolution(u32 monitor)
	{
		ASSERT(nullptr != g_Provider, "No global monitor provider set");

		return g_Provider->resolution(monitor);
	}

	IMonitorProvider *get_provider()
	{
		return g_Provider.get();
	}
}
