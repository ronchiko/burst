#pragma once

#include <memory>

#include <Burst/Common/Types.h>
#include <Burst/Common/Presentables/IWindow.h>

namespace burst::glfw {
	/**
	 * Creates a new GLFW window.
	 */
	Unique<burst::IWindow> make_window(
		u32 width, u32 height, const String& title
	);
}
