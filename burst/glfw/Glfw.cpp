#include "burst/Glfw.h"

#include <burst/common/Input.h>

#include "burst/glfw/Error.h"
#include "burst/glfw/Window.h"
#include "burst/glfw/KeyInputProvider.h"

static void glfw_error_hanlder(burst::i32 code, burst::cstr message) {
	throw burst::glfw::Error(message, code);
}

static void initialize_glfw() {
	static bool g_Initialized = false;
	if (g_Initialized) return;

	if (glfwInit() != GLFW_TRUE) {
		throw burst::glfw::Error("Failed to initialize GLFW", 0);
	}

	glfwSetErrorCallback(&glfw_error_hanlder);
	burst::input::register_key_provider(
		std::make_unique<burst::glfw::KeyInputProvider>()
	);
	
	g_Initialized = true;
}

std::unique_ptr<burst::Window> burst::glfw::make_window(const burst::WindowInfo& info) {
	initialize_glfw();
	
	auto window = std::make_unique<burst::glfw::Window>(
			info.title,
			info.width,
			info.height
		);
	window->info(info);
	return window;
}
