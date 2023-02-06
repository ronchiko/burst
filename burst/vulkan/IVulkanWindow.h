#pragma once

#include <burst/common/Presentables/IWindow.h>

#include "Instance/Requirement.h"


namespace burst::vulkan {
	/**
	 * A window that can be used with the vulkan renderer.
	 */
	class IVulkanWindow : public IWindow
	{
	public:
		/**
		 * Gets the vulkan requirements for this window.
		 */
		IFACE_FUNC(Vector<Requirement> get_requirements() const);
	};
}
