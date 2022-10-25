
#include <burst/Common.h>
#include <burst/Glfw.h>
#include <burst/Vulkan.h>

int main() {
	burst::log::add_logger(
		std::make_unique<burst::log::ConsoleLogger>()
	);

	auto window = burst::glfw::make_window(burst::WindowInfo{
		"My Application",
		512,
		512,
		burst::WindowMode::WINDOWED
	});

	auto vulkan = burst::vulkan::load_default_instance(
		"My Application",
		10,
		window.get()
	);

	while (!window->should_quit()) {
		window->render();
	}
}