#pragma once

#include <string>
#include <vector>

#include "Types.h"
#include "Framebuffer.h"

namespace burst {

	enum class WindowMode {
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
	class Window {
	public:
		virtual ~Window() = default;

		virtual bool should_quit() = 0;

		virtual void render() = 0;

		/**
		 * @brief: Gets the window information about this window
		 */
		virtual WindowInfo info() const = 0;

		/**
		 * @brief: Sets the window information about this window 
		 */
		virtual void info(const WindowInfo&) = 0;

		/**
		 * Gets the vulkan requirements for this window
		 */  
		virtual std::vector<cstr> get_requirements() const = 0;

		/**
		 * Gets the window handle for this object
		 */
		virtual void* window_handle() const = 0;

		/**
		 * Gets the frame buffer for with window
		 */
		virtual Framebuffer& framebuffer() = 0;
	};
}