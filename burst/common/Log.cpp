#include "Log.h"

#include <vector>
#include <memory>

static std::vector<std::unique_ptr<burst::log::Logger>> g_Writers;

void burst::log::add_logger(std::unique_ptr<burst::log::Logger> writer) {
	g_Writers.push_back(std::move(writer));
}

void burst::log::log(burst::log::Level level, const std::string& message) {
	for (auto& writer : g_Writers) {
		writer->log(level, message);
	}
}
