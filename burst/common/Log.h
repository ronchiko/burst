#pragma once

#include <string>

#include "Meta.h"
#include "Logger.h"

namespace burst::log {
	void add_logger(std::unique_ptr<burst::log::Logger> writer);

	void log(Level level, const std::string& message);

	template<typename... T>
	void debug(const T&... args) {
		log(Level::DEBUG, burst::concat(args...));
	}

	template<typename... T>
	void info(const T&... args) {
		log(Level::INFO, burst::concat(args...));
	}
	
	template<typename... T>
	void warning(const T&... args) {
		log(Level::WARNING, burst::concat(args...));
	}

	template<typename... T>
	void error(const T&... args) {
		log(Level::ERROR, burst::concat(args...));
	}
}
