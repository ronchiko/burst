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
		virtual ~IVulkanWindow() = default;
		/**
		 * Gets the vulkan requirements for this window.
		 */
		virtual Vector<Requirement> get_requirements() const = 0;
	};
}
