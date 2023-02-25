#include "burst/Vulkan.h"

#include <vulkan/vulkan.hpp>

#include <burst/common/Print.h>

#include "Instance/Gpu/Gpu.h"
#include "Instance/Instance.h"

#include "Renderer/Renderer.h"
#include "Utils/Extensions.h"

namespace burst::vulkan {

	static void log_available_extensions()
	{
		std::stringstream ss;
		ss << "Available extenions: " << std::endl
		   << pretty_iterable(all_extensions(), "* ", 5);

		log::info(ss.str());
	}

	static void log_available_layers()
	{
		std::stringstream ss;
		ss << "Available layers: " << std::endl
		   << pretty_iterable(all_layers(), "* ", 5);

		log::info(ss.str());
	}

	Unique<IRenderer> create_vulkan_render(const ApplicationInfo& info,
										   Shared<Configuration> configuration,
										   IVulkanWindow& window)
	{
		log_available_extensions();
		log_available_layers();


		Unique<Renderer> renderer =
			std::make_unique<Renderer>(info, configuration, window);
		return renderer;
	}
}
