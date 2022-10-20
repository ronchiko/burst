#include "Instance.h"

#include <burst/Common.h>

#include "Const.h"
#include "Errors.h"

/**
 * Throws an exception if not all required extensions are available
 */
void assert_all_required_extensions_available(const std::vector<burst::cstr>& required)
{
	auto available = vk::enumerateInstanceExtensionProperties();
	std::vector<std::string> missing;

	for (auto& extension : required) {
		if (available.end() == std::find_if(
			available.begin(),
			available.end(),
			[&extension](const vk::ExtensionProperties& ext) {
				return std::string(ext.extensionName.data()) == extension;
			}))
		{
			missing.push_back(extension);
		}
	}

	if (missing.size() > 0) {
		std::stringstream message;
		message << "Missing required extensions: \n";
		for (int i = 0; i < missing.size(); ++i) {
			message << missing[i] << (i == missing.size() - 1 ? "" : "\n");
		}
		burst::log::error(message.str());

		throw burst::vulkan::MissingRequiredComponentsError();
	}
}

/**
 * Throws an exception if not all required validtion layers are available
 */
void assert_all_required_validtion_layers_available(const std::vector<burst::cstr>& required)
{
	auto available = vk::enumerateInstanceLayerProperties();
	std::vector<std::string> missing;

	for (auto& layer : required) {
		if (available.end() == std::find_if(
			available.begin(),
			available.end(),
			[&layer](const vk::LayerProperties& layer_properties) {
				return std::string(layer_properties.layerName.data()) == layer;
			}))
		{
			missing.push_back(layer);
		}
	}

	if (!missing.empty()) {
		std::stringstream message;
		message << "Missing required layers: \n";
		for (int i = 0; i < missing.size(); ++i) {
			message << missing[i] << (i == missing.size() - 1 ? "" : "\n");
		}
		burst::log::error(message.str());

		throw burst::vulkan::MissingRequiredLayersError();
	}
}

[[nodiscard]]
static vk::raii::Instance _create_unsafe_instance(
	burst::cstr name,
	burst::u32 version,
	burst::Window* window,
	burst::vulkan::InstanceRequirements& requirements
) {
	using namespace burst;
	using namespace burst::vulkan;

	auto extensions = iter_convert<std::vector<cstr>>(requirements.extensions);
	auto validtion_layers = iter_convert<std::vector<cstr>>(requirements.validation_layers);

	assert_all_required_extensions_available(extensions);
	assert_all_required_validtion_layers_available(validtion_layers);

	vk::ApplicationInfo application_info = APPLICATION_INFO;
	application_info.applicationVersion = version;
	application_info.pApplicationName = name;

	vk::InstanceCreateInfo create_info(
		vk::InstanceCreateFlags(),
		&application_info,
		validtion_layers,
		extensions
	);

	return vk::raii::Instance(vk::raii::Context(), create_info);
}

namespace burst::vulkan {
	
	Instance::Instance(vk::raii::Instance instance, Map map, InstanceRequirements r)
		: m_Instance(std::move(instance))
		, m_Components(std::move(map))
		, m_Requirements(std::move(r))
	{
		for (const auto& component : m_Components) {
			component.second->init(m_Instance, AdditionalCreateInfo{});
		}
	}

	const vk::raii::Instance& Instance::instance() const {
		return m_Instance;
	}

	const InstanceRequirements Instance::requirements() const {
		return m_Requirements;
	}

	Instance make_instance(
		cstr name,
		u32 version,
		InstanceComponentVector& components,
		Window* window
	) {
		InstanceRequirements requirements;
		for (const auto& component : components) {
			component->add_requirements(requirements);
		}
		
		Instance::Map map;
		for (auto& component : burst::pull_children_of<IInstanceComponent>(components)) {
			const auto id = typeid(*component).hash_code();
			map[id] = std::move(component);
		}

		auto vk_instance = _create_unsafe_instance(name, version, window, requirements);
		burst::log::debug("Successfuly created vk::Instance");
		return Instance(std::move(vk_instance), std::move(map), std::move(requirements));
	}
}
