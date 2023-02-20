#include "Instance/Instance.h"

#include <ranges>

#include <burst/Common.h>

/**
 * Coverts a burst version to vulkan version.
 *
 * \param version: The burst version
 */
static burst::u32 convert_version(const burst::Version& version)
{
	return VK_MAKE_VERSION(version.major, version.minor, version.fix);
}

/**
 * Creates a vulkan applicaiton info from the burst application info.
 */
static vk::ApplicationInfo
create_application_info(const burst::ApplicationInfo& info)
{
	return vk::ApplicationInfo(info.application_name.c_str(),
							   convert_version(info.application_version),
							   burst::engine::NAME,
							   convert_version(burst::engine::VERSION),
							   VK_API_VERSION_1_3);
}

namespace burst::vulkan {

	/**
	 * Creates a new vulkan instance.
	 */
	static vk::raii::Instance create_instance(const ApplicationInfo& info,
											  const Configuration& config,
											  IVulkanWindow& window)
	{
		auto all_requirements = config.requirements;
		auto window_requirements = window.get_requirements();

		for(const auto& req : window.get_requirements()) {
			all_requirements.push_back(req);
		}

		auto extensions = select_requirements(all_requirements,
											  RequirementType::InstanceExtension);

		auto layers =
			select_requirements(all_requirements, RequirementType::ValidationLayer);
		auto app_info = create_application_info(info);

		vk::InstanceCreateInfo create_info(
			vk::InstanceCreateFlags(0), &app_info, layers, extensions);

		auto instance = vk::createInstance(create_info);
		return vk::raii::Instance(vk::raii::Context{}, instance);
	}

	Instance::Instance(const ApplicationInfo& info,
					   const Configuration& config,
					   IVulkanWindow& window)
		: m_Instance(create_instance(info, config, window))
		, m_Messenger()
	{
#ifdef _DEBUG
		// Messenger only if in debug mode

		m_Messenger = DebugMessenger(*this);
#endif
	}

	Vector<Gpu> Instance::gpus() const
	{
		auto gpus = m_Instance.enumeratePhysicalDevices();

		return convert<Vector<Gpu>>(gpus,
									[](const vk::raii::PhysicalDevice& device) {
										return Gpu(std::move(device));
									});
	}

	Instance::operator vk::Instance() const
	{
		return *m_Instance;
	}

	Instance::operator vk::raii::Instance &()
	{
		return m_Instance;
	}
}
