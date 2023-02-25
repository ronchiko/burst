#include <iostream>

#include <burst/Common.h>
#include <burst/Glfw.h>
#include <burst/Vulkan.h>

#include <burst/Common/Optimize/Avx.h>

#include <burst/common/Flags.h>

#include <Windows.h>

const burst::ApplicationInfo INFO{
	"Demo App",
	burst::Version(1),
};

struct F : public burst::IScalingPresentableListener
{
	virtual void on_scale_changed(burst::u32 width, burst::u32 height) {
		burst::log::debug("called f");
	}
};

int main()
{
	using namespace burst;

	Vector<int> v{ 1, 2, 3, 4 };

	// Initialize logger
	log::add_logger(std::make_unique<burst::log::ConsoleLogger>());

	// Create a new window with the GLFW window provider
	log::debug("Creating window");
	auto window = glfw::make_window(512, 512, INFO.application_name);

	// Ensure the window is compatible with vulkan
	if(nullptr == dynamic_cast<burst::vulkan::IVulkanWindow *>(window.get())) {
		log::info("Window creator is not compatible with vulkan");
		return 1;
	}

	//try {
		// Create a new vulkan renderer
		log::debug("Creating renderer");
		auto renderer = vulkan::create_vulkan_render(
			INFO,
			vulkan::Configuration::create_default_configuration(),
			*reinterpret_cast<vulkan::IVulkanWindow *>(window.get()));

		log::info("Starting game mainloop! :)");
		while(window->is_active()) {
			renderer->render();
			window->update();
		}
	/*}
	catch (const std::exception& e) {
		log::error(typeid(e).name(), ": ", e.what());
	}*/
	
}