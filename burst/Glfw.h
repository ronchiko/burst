#pragma once

#include <memory>

#include <Burst/Common.h>

#include "burst/glfw/Error.h"

namespace burst::glfw {
	/**
	 * @brief Creates a new GLFW window
	 */
	std::unique_ptr<burst::IWindow> make_window(
		u32 width, u32 height, const std::string& title
	);
}
