#include "ConsoleLogger.h"

#include <iostream>
#include <unordered_map>

static const std::unordered_map<burst::log::Level, std::string> PREFIXES({
	{ burst::log::Level::DEBUG,		"\033[32m[Debug]\033[0m:" },
	{ burst::log::Level::INFO,		"\033[34;1m[Info]\033[0m:" },
	{ burst::log::Level::WARNING,	"\033[33;1m[Warning]\033[0m:" },
	{ burst::log::Level::ERROR,		"\033[31;1m[Error]\033[0m:" },
});

void burst::log::ConsoleLogger::log(burst::log::Level level, const std::string& message) {
	std::cout << PREFIXES.at(level) << message << std::endl;
}
