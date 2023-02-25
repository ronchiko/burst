#pragma once

#include <GLFW/glfw3.h>

#include <burst/common/Types/Notifier.h>

namespace burst::glfw {
	/**
	 * Event listener for a window is resized.
	 */
	class IResizeEventListener
	{
	public:
		virtual ~IResizeEventListener() = default;

		/**
		 * Invoked when a window is resized.
		 * 
		 * \param window: The window that was resized
		 * \param width: The window width
		 * \param height: The window height
		 */
		virtual void on_window_resized(GLFWwindow *window, int width, int height) = 0;
	};

	inline Notifier<IResizeEventListener> g_ResizeEventNotifier = {};

	/**
	 * GLFW framebuffer resize event handler
	 */
	inline void glfw_resize_event(GLFWwindow* window, int width, int height) {
		g_ResizeEventNotifier.notify(&IResizeEventListener::on_window_resized, window, width, height);
	}
}
