#pragma once

#include "Application.h"

/**
 * Provides information about the engine.
 */
namespace burst::engine {
	/**
	 * An enum containing all the version of the engine.
	 */
	struct AllVersions
	{
		static constexpr Version DEVELOPMENT{0, 0 ,0};
	};

	/**
	 * The version of the engine.
	 */
	inline constexpr Version VERSION = AllVersions::DEVELOPMENT;

	/**
	 * The name of the engine.
	 */
	inline constexpr const char *NAME = "Burst Engine";
}
