#pragma once

#include <GLFW/glfw3.h>

#include <burst/common/Types/Notifier.h>

namespace burst::glfw {

	/**
	 * Interface for listening for glfw key events.
	 */
	class IKeyEventListener
	{
	public:
		virtual ~IKeyEventListener() = default;

		/**
		 * Invoked when a key is .
		 *
		 * \param window
		 * \param key
		 * \param scancode
		 * \param action
		 * \param mods
		 */
		virtual void on_key_event(GLFWwindow *window, int key, int scancode, int action, int mods) = 0;
	};

	inline Notifier<IKeyEventListener> g_KeyEventNotifier = {};

	/**
	 * GLFW key event handler for burst.
	 */
	inline void glfw_key_event(GLFWwindow *window, int key, int scancode, int action, int mods)
	{
		g_KeyEventNotifier.notify(&IKeyEventListener::on_key_event, window, key, scancode, action, mods);
	}
}
