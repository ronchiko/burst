#pragma once

#include <set>

#include <vulkan/vulkan_raii.hpp>

#include <burst/Common.h>

#include "IInstanceDependent.h"

namespace burst::vulkan {

	INTERFACE IInstanceComponent : public IInstanceDependent{
	public:
		IFACE_DESTRUCTOR(IInstanceComponent);

		/**
		 * Initializes the component.
		 *
		 * \param instance: The instance that was created
		 * \param create_info: Additional creation info from the instance creation
		 */
		IFACE_FUNC(void init(
			const vk::raii::Instance& instance,
			const AdditionalCreateInfo& create_info
		));
	};

	template<typename T>
	concept InstanceComponent = requires
	{
		{ T() } -> std::derived_from<IInstanceComponent>;
	};
}
