#include "ConsoleLogger.h"

#include <iostream>
#include <unordered_map>

namespace burst::log {

	static const HashMap<LogSeverity,String> PREFIXES({
		{ LogSeverity::DEBUG, "\033[32m[Debug]\033[0m: " },
		{ LogSeverity::INFO, "\033[34;1m[Info]\033[0m: " },
		{ LogSeverity::WARNING, "\033[33;1m[Warning]\033[0m: " },
		{ LogSeverity::ERROR, "\033[31;1m[Error]\033[0m: " },
	});

	void ConsoleLogger::log(LogSeverity level, const String& message)
	{
		std::cout << PREFIXES.at(level) << message << std::endl;
	}
}
