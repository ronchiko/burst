#pragma once

#include "../IDynamicStateHandler.h"

namespace burst::vulkan {
	/**
	 * Dynamic state handler for a viewport.
	 */
	class DynamicViewportHandler : public IDynamicStateHandler
	{
	public:
		/**
		 * Gets the state of the viewport handler.
		 */
		inline virtual Vector<vk::DynamicState> get_states() const override
		{
			return { vk::DynamicState::eViewport, vk::DynamicState::eScissor };
		}


	};
}
