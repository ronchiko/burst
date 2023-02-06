#pragma once

#include "../Types.h"

namespace burst::monitor {
	/**
	 * A class that provides information about the monitor.
	 */
	class IMonitorProvider
	{
	public:
		IFACE_DESTRUCTOR(IMonitorProvider);

		/**
		 * Provides the resolution of the monitor.
		 */
		IFACE_FUNC(Uint2 resolution(u32 index) const);
	};

	/** Index of the main monitor */
	inline constexpr u32 MAIN_MONITOR = std::numeric_limits<u32>::max();

	/**
	 * Sets the active monitor provider.
	 * 
	 * \param provider: The new provider object
	 */
	void set_provider(Shared<IMonitorProvider> provider);

	/**
	 * Gets the resolution of the monitor.
	 */
	Uint2 resolution(u32 index = MAIN_MONITOR);

	/**
	 * Gets the current provider.
	 * 
	 * \note: Prefer to use the other exposed functions
	 */
	IMonitorProvider *get_provider();
}



