#pragma once

#include "Logger.h"

namespace burst::log {
	class ConsoleLogger : public Logger {
	public:
		virtual void log(Level level, const std::string& message) override;
	};
}
