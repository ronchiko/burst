#pragma once

#include <optional>

#include <vulkan/vulkan.h>

#include <burst/Common.h>

#include "Component.h"

namespace burst::vulkan {

	enum class QueueFamilyType {
		Graphics,
		Present
	};

	struct QueueFamilyInfo {
		u32 index;
		VkQueueFamilyProperties properties;
		VkPhysicalDevice physical_device;
		std::optional<VkSurfaceKHR> surface;
	};

	class QueueFamilyHandler {
	public:
		virtual ~QueueFamilyHandler() = default;

		/**
		 * Handles the queue family info
		 */
		virtual void handle_queue_family(const QueueFamilyInfo& info) = 0;

		/**
		 * Returns true if the queue is valid and usable
		 */
		virtual bool is_complete() const = 0;

		/**
		 * Gets the index family of a known family
		 */
		virtual std::optional<u32> get_known_family(QueueFamilyType family) const = 0;

		/**
		 * Given a VkDeviceQueueCreateInfo configures it according to the handlers values
		 */
		virtual std::vector<VkDeviceQueueCreateInfo> create_queue_creation_infos() const = 0;
	};

	template<class T>
	concept QueueFamily = requires(T a) {
		{ T() } -> std::derived_from<QueueFamilyHandler>;
		{ std::move(a) };
	};
}


