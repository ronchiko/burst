#include "Device.h"

static std::vector<float> g_QueuePriorities = {1.f};

/**
 * Makes the queue create infos from the gpu queues.
 */
static std::vector<vk::DeviceQueueCreateInfo> make_queue_list(
	const burst::vulkan::GpuQueues& queues
) {
	std::set<burst::u32> unique = {
		queues[burst::vulkan::QueueType::Graphics].value(),
		queues[burst::vulkan::QueueType::Present].value(),
	};
	std::vector<vk::DeviceQueueCreateInfo> queues_create_info;
	queues_create_info.reserve(unique.size());

	for (auto& queue : unique) {
		queues_create_info.push_back(vk::DeviceQueueCreateInfo(
			vk::DeviceQueueCreateFlags(),
			queue,
			g_QueuePriorities
		));
	}

	return queues_create_info;
}
/**
 * Creates a device from a GPU.
 */
static vk::raii::Device create_device(burst::vulkan::Gpu& gpu) {
	using namespace std;
	using namespace burst;

	auto queue_create_infos = make_queue_list(gpu.queues());
	const auto& requirements = gpu.instance().requirements();

	auto layers = burst::iter_convert<vector<cstr>>(requirements.validation_layers);
	auto extensions = burst::iter_convert<vector<cstr>>(requirements.device_extensions);

	vk::PhysicalDeviceFeatures features;

	vk::DeviceCreateInfo info(
		vk::DeviceCreateFlags(),
		queue_create_infos,
		layers,
		extensions,
		&features
	);

	return vk::raii::Device(gpu.device(), info);
}

static burst::vulkan::Device::Map extract_components(
	burst::vulkan::InstanceComponentVector& components
) {
	using namespace burst::vulkan;

	Device::Map map;
	for (auto& component : burst::pull_children_of<IDeviceComponent>(components)) {
		map[typeid(*component).hash_code()] = std::move(component);
	}

	return map;
}

namespace burst::vulkan {
	Device::Device(
		Gpu& gpu, 
		InstanceComponentVector& components,
		const AdditionalCreateInfo& create_info
	) : m_Gpu(gpu),
		m_Device(create_device(gpu)),
		m_Components(extract_components(components))
	{
		burst::log::debug("Created vk::Device successfully");
		for (auto& [_, component] : m_Components) {
			component->init(m_Device, gpu, create_info);
		}
	}

	const Gpu& Device::gpu() const {
		return m_Gpu;
	}

	const vk::raii::Device& Device::device() const {
		return m_Device;
	}
}
