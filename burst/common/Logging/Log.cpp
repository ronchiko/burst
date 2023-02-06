#include "Log.h"

#include <vector>
#include <memory>

namespace burst::log {

	static Vector<Unique<ILogger>> g_Writers;

	void add_logger(Unique<ILogger> writer)
	{
		g_Writers.push_back(std::move(writer));
	}

	void log(LogSeverity severity, const String& message)
	{
		for(auto& writer : g_Writers) {
			writer->log(severity, message);
		}
	}
}
