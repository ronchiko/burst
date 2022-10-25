#include "Gpu.h"

#include <map>

#include "Errors.h"

namespace burst::vulkan {

	Gpu::Gpu(
		vk::raii::PhysicalDevice device,
		Instance& instance,
		Map components,
		GpuQueues queues,
		const AdditionalCreateInfo& create_info
	) : m_Device(device), 
		m_Parent(instance), 
		m_Components(std::move(components)),
		m_Queues(queues)
	{
		for (auto& component : m_Components) {
			component.second->init(device, instance, create_info);
		}
	}

	const vk::raii::PhysicalDevice& Gpu::device() const {
		return m_Device;
	}

	const Instance& Gpu::instance() const {
		return m_Parent;
	}

	std::string Gpu::name() const {
		return m_Device.getProperties().deviceName;
	}

	vk::PhysicalDeviceLimits Gpu::limits() const {
		return m_Device.getProperties().limits;
	}

	vk::PhysicalDeviceType Gpu::type() const {
		return m_Device.getProperties().deviceType;
	}

	const GpuQueues& Gpu::queues() const {
		return m_Queues;
	}

	GpuAnalyzer::GpuAnalyzer(const Instance& instance)
		: m_Instance(instance) {}

	Gpu pick_best_gpu(
		Instance& instance,
		InstanceComponentVector& components,
		GpuAnalyzer& rater,
		const AdditionalCreateInfo& info
	) {
		struct DeviceInfo {
			vk::raii::PhysicalDevice device;
			GpuAnalyzer::Score score;
		};

		auto gpus = instance.instance().enumeratePhysicalDevices();

		std::multimap<u32, DeviceInfo> ranking;
		for (const auto& _gpu : gpus) {
			Gpu gpu(_gpu, instance, {}, {}, info);
			
			auto result = rater(gpu);
			if (result.score > GpuAnalyzer::SCORE_EXCLUDE) {
				ranking.insert(std::make_pair(
					result.score,
					DeviceInfo{ _gpu, result}
				));
			}
		}

		if (ranking.empty()) {
			burst::log::error("No suitable GPU found, aborting!");
			throw NoSuitableGpuError();
		}

		Gpu::Map map;
		auto [score, gpu_info] = *(--ranking.end());
		for (auto& component : pull_children_of<IGpuComponent>(components)) {
			uid id = typeid(*component).hash_code();
			map[id] = std::move(component);
		}

		Gpu gpu(gpu_info.device, instance, std::move(map), gpu_info.score.queues, info);
		burst::log::info("Most suitable GPU is: ", gpu.name());

		return gpu;
	}
}
