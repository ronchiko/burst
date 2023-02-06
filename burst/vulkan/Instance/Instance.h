#pragma once

#include <vulkan/vulkan_raii.hpp>

#include <burst/Common.h>

#include "../Configuration.h"
#include "../IVulkanWindow.h"
#include "DebugMessenger.h"

namespace burst::vulkan {

	class Gpu;

	/**
	 * A vulkan instance.
	 */
	class Instance
	{
	public:
		/**
		 * Creates a new application instance.
		 * 
		 * \param info: The info about the creating application
		 * \param config: The configuration of the application
		 */
		explicit Instance(const ApplicationInfo& info, const Configuration& config, IVulkanWindow& window);

		/**
		 * Gets a vector of all the GPUs vulkan detects for this instance.
		 */
		Vector<Gpu> gpus() const;

		/**
		 * Convert to non owning vk::Instance.
		 */
		operator vk::Instance() const;

		/**
		 * Convert to owning vk::Instance.
		 */
		explicit operator vk::raii::Instance&();

	private:
		vk::raii::Instance m_Instance;
		DebugMessenger m_Messenger;
	};
	
}
