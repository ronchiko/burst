#pragma once

#include "ILogger.h"

namespace burst::log {
	/**
	 * A logger that writes the console.
	 */
	class ConsoleLogger : public ILogger {
	public:
		/**
		 * Writes a log message to the console.
		 */
		virtual void log(LogSeverity level, const String& message) override;
	};
}


