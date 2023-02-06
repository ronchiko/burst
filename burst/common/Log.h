#pragma once

#include <burst/common/Meta.h>
#include <burst/common/Logging/ILogger.h>

namespace burst::log {
	/**
	 * Adds a logger to the loggers list.
	 *
	 * \param writer - The logger
	 */
	void add_logger(Unique<ILogger> logger);

	/**
	 * Writes a log to all the registered loggers.
	 *
	 * \param level - The severity of the log message
	 * \param message - The message to log
	 */
	void log(LogSeverity severity, const std::string& message);

	template<typename... T>
	void debug(const T&...args)
	{
#ifdef _DEBUG
		log(LogSeverity::DEBUG, burst::concat(args...));
#endif
	}

	template<typename... T>
	void info(const T&...args)
	{
		log(LogSeverity::INFO, burst::concat(args...));
	}

	template<typename... T>
	void warning(const T&...args)
	{
		log(LogSeverity::WARNING, burst::concat(args...));
	}

	template<typename... T>
	void error(const T&...args)
	{
		log(LogSeverity::ERROR, burst::concat(args...));
	}
}
