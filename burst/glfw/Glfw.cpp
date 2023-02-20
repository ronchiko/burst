#include "burst/Glfw.h"

#include <burst/Common.h>

#include "burst/glfw/Error.h"
#include "burst/glfw/KeyInputProvider.h"
#include "burst/glfw/Window.h"

namespace burst::glfw {

	static void glfw_error_hanlder(burst::i32 code, burst::cstr message)
	{
		// throw burst::glfw::GlfwError(message, code);
	}

	static void initialize_glfw()
	{
		static bool g_Initialized = false;
		if(g_Initialized) return;

		if(glfwInit() != GLFW_TRUE) {
			throw burst::glfw::GlfwError("Failed to initialize GLFW");
		}

		glfwSetErrorCallback(&glfw_error_hanlder);
		burst::input::register_key_provider(std::make_unique<burst::glfw::KeyInputProvider>());

		g_Initialized = true;
	}

	Unique<IWindow> make_window(u32 width, u32 height, const String& title)
	{
		initialize_glfw();

		auto window = std::make_unique<Window>(title, width, height);
		return window;
	}
}