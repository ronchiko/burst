#include "SurfaceSupportOptions.h"

bool burst::vulkan::SurfaceSupportOptions::is_ok() const {
	return !formats.empty() && !present_modes.empty();
}

