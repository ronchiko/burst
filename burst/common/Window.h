#pragma once

#include <string>
#include <vector>

#include "Types.h"
#include "Framebuffer.h"

namespace burst {

	ENUM WindowMode {
		WINDOWED,
		FULLSCREEN
	};

	struct WindowInfo {
		std::string title;
		burst::i32 width;
		burst::i32 height;
		WindowMode fullscreen;
	};

	/**
	 * @brief: Interface for creating a window
	 */
	INTERFACE Window {
	public:
		IFACE_DESTRUCTOR(Window);

		IFACE_FUNC(bool should_quit());

		IFACE_FUNC(void render());

		/**
		 * @brief: Gets the window information about this window
		 */
		IFACE_FUNC(WindowInfo info() const);

		/**
		 * @brief: Sets the window information about this window 
		 */
		IFACE_FUNC(void info(const WindowInfo&));

		/**
		 * Gets the vulkan requirements for this window
		 */  
		IFACE_FUNC(std::vector<cstr> get_requirements() const);

		/**
		 * Gets the window handle for this object
		 */
		IFACE_FUNC(void* window_handle() const);

		/**
		 * Gets the frame buffer for with window
		 */
		IFACE_FUNC(Framebuffer& framebuffer());
	};
}