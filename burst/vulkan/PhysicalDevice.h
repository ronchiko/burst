#pragma once

#include <map>

#include <vulkan/vulkan.h>

#include <burst/common/Error.h>

#include "Component.h"
#include "QueueFamilyHandler.h"

namespace burst::vulkan {

	constexpr u32 SCORE_EXCLUDE_DEVICE = 0;

	class DeviceNotFoundError : public StaticError {
	public:
		explicit DeviceNotFoundError(burst::cstr message);
	};

	u32 default_physical_device_rater(
		const VkPhysicalDeviceProperties& properties,
		const VkPhysicalDeviceFeatures& features
	);

	/**
	 * Represents a vulkan physical device
	 */
	class PhysicalDevice {
	public:
		using Rater = decltype(&default_physical_device_rater);

		PhysicalDevice(VkPhysicalDevice device);

		/**
		 * Selects the most suitable physical device available
		 */
		template<QueueFamily Q>
		static PhysicalDevice select_suitable(
			VkInstance instance,
			const CStrVector& device_extensions,
			std::optional<VkSurfaceKHR> surface = {},
			Rater rater = default_physical_device_rater
		) {
			auto devices = query_devices(instance);

			std::multimap<u32, VkPhysicalDevice> rated_device;
			for (const auto& device : devices) {
				PhysicalDevice physical_device{ device };

				Q queue_family_handler;
				physical_device.find_queue_indecies(queue_family_handler, surface);
				u32 rating = physical_device.rate(
					device_extensions,
					queue_family_handler,
					rater);
				rated_device.insert(std::make_pair(rating, device));
			}

			auto& [score, device] = *rated_device.rbegin();
			if (score <= 0) {
				throw DeviceNotFoundError("Not suitable GPU found.");
			}

			return PhysicalDevice{ device };
		}
		
		/**
		 * Gets the vulkan physical device object owned by this object
		 */
		VkPhysicalDevice device() const;

		/**
		 * Gets the queue indecies for this physical device
		 */
		void find_queue_indecies(
			QueueFamilyHandler& handler,
			std::optional<VkSurfaceKHR> surface = {}
		) const;

	private:
		u32 rate(
			const CStrVector& device_extensions,
			QueueFamilyHandler& queue_family_handler,
			Rater selector = default_physical_device_rater
		);

		/**
		 * Queries all existing devices for an instance
		 */
		static std::vector<VkPhysicalDevice> query_devices(VkInstance);

		/**
		 * Gets the available extensions for this physical device
		 */
		std::vector<VkExtensionProperties> get_available_extensions() const;

		/**
		 * Checks if a vector device extensions are supported
		 */
		bool check_device_extensions_supported(const CStrVector&) const;

		VkPhysicalDevice m_Device;
	};
}
