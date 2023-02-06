#pragma once

#include <vulkan/vulkan.hpp>

#include <burst/common/Types.h>

namespace burst::vulkan {
	/**
	 * Pipeline dynamic state interface.
	 */
	class IDynamicStateHandler
	{
	public:
		virtual ~IDynamicStateHandler() = default;

		/**
		 * Gets the vulkan dynamic state this dynamic state handler is handling.
		 * 
		 * \return: The VkDynamicState the handler is handling
		 */
		virtual Vector<vk::DynamicState> get_states() const = 0;
	};
}
