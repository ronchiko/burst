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
		virtual ~IWindow() = default;
		/**
		 * Gets the window identifier for this window
		 */
		virtual Identifier identifier() const = 0;
	};
}
