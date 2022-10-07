#pragma once

#include <string>

namespace burst::log {
	enum class Level {
		DEBUG,
		INFO,
		WARNING,
		ERROR
	};

	class Logger {
	public:
		virtual ~Logger() = default;

		virtual void log(Level level, const std::string& message) = 0;
	};
}
