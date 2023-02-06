#pragma once

#include <string>
#include <vector>

#include "../Types.h"
#include "IRealtimePresentable.h"

namespace burst {

	/**
	 * @brief: Interface for creating a window
	 */
	class IWindow : public IRealtimePresentable
	{
	public:
#ifdef _WIN32
		/** The OS specific identifier for a window (HANDLE for windows)*/
		using Identifier = void *;
#else // Currently only windows is supported
#error The engine does not support this OS
#endif
		IFACE_DESTRUCTOR(IWindow);
		/**
		 * Gets the window identifier for this window
		 */
		IFACE_FUNC(Identifier identifier() const);
	};
}
