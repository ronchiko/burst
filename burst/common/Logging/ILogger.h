#pragma once

#include <string>

#include "../Types.h"

namespace burst::log {
	/**
	 * The severity of a log.
	 */
	enum class LogSeverity
	{
		DEBUG,
		INFO,
		WARNING,
		ERROR
	};

	/**
	 * Interface for loggers.
	 */
	class ILogger
	{
	public:
		IFACE_DESTRUCTOR(ILogger);

		/**
		 * Logs a message.
		 *
		 * \param level: The severity of the message
		 * \param message: The message to log
		 */
		IFACE_FUNC(void log(LogSeverity level, const String& message));
	};
}
