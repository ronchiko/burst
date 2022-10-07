#pragma once

#include <memory>

#include <burst/common/Window.h>

#include "burst/glfw/Error.h"

namespace burst::glfw {
	/**
	 * @brief Creates a new GLFW window
	 */
	std::unique_ptr<burst::Window> make_window(
		const burst::WindowInfo& info
	);
}
