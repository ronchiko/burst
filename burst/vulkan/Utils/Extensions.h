#pragma once

#include "../Instance/Requirement.h"

namespace burst::vulkan {
	/**
	 * Checks if a requirement is supported on this device.
	 *
	 * \param requirement: The requirement to check
	 */
	bool is_requirement_supported(Requirement requirement);

	/**
	 * All the layers available for this machine.
	 */
	Set<String> all_layers();

	/**
	 * All the extensions available for this machine.
	 */
	Set<String> all_extensions();
}
