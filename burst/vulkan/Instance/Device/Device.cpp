#include "Device.h"

#include <ranges>

#include "../Gpu/Gpu.h"


namespace burst::vulkan {

	/**
	 * Given the queue information for a device figures if that device is capable of
	 * rendering.
	 *
	 * \param queues: The queue info about the device
	 */
	static bool is_rendering_device(Queues& queues)
	{
		return queues.has_queue(QueueType::Graphics) &&
			   queues.has_queue(QueueType::Present);
	}

	/**
	 * Create the queues create info list.
	 *
	 * \param queues: The queues strucutre to create the create info to
	 */
	static Vector<vk::DeviceQueueCreateInfo> make_queue_create_infos(Queues& queues)
	{
		using namespace std::views;

		static Vector<f32> s_QueuePriorities = { 1.f };

		// This device doesnt have all the required queues to be used for
		// renderering, then no queues are needed.
		if(!is_rendering_device(queues)) {
			return {};
		}

		Set<u32> queue_indecies = {
			queues[QueueType::Graphics].value(),
			queues[QueueType::Present].value(),
		};

		auto result = queue_indecies | transform([](const u32& queue) {
						  return vk::DeviceQueueCreateInfo{
							  vk::DeviceQueueCreateFlags(0),
							  queue,
							  s_QueuePriorities,
						  };
					  });

		return { result.begin(), result.end() };
	}

	/**
	 * Creates a vulkan device object.
	 *
	 * \param gpu: The gpu to bind the device to
	 * \param queues: The queues used by the device
	 * \param configuration: The configuration to uses
	 */
	static vk::raii::Device
	create_device(Gpu& gpu, Queues& queues, const Configuration& configuration)
	{
		auto q = make_queue_create_infos(queues);
		auto requirements = select_requirements(configuration.requirements,
												RequirementType::DeviceExtension);
		auto layers = select_requirements(configuration.requirements,
										  RequirementType::ValidationLayer);

		vk::DeviceCreateInfo info(vk::DeviceCreateFlags(0), q, layers, requirements);

		return vk::raii::Device(static_cast<vk::raii::PhysicalDevice&>(gpu), info);
	}

	Device::operator vk::raii::Device &()
	{
		return m_Device;
	}

	Device::operator vk::Device() const
	{
		return *m_Device;
	}

	Queue Device::get_queue(u32 family_index, u32 index) const
	{
		return Queue((*m_Device).getQueue(family_index, index));
	}

	Device::Device(Gpu& gpu, Queues& queues, Shared<Configuration> configuration)
		: m_Device(create_device(gpu, queues, *configuration))
		, m_IsRendering(is_rendering_device(queues))
	{}
}
