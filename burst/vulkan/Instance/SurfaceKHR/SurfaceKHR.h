#pragma once

#include <vulkan/vulkan_raii.hpp>

#include <burst/common/Presentables/IWindow.h>

namespace burst::vulkan {

	class Instance;

	class SurfaceKHR
	{
	public:

		/**
		 * Creates a new surfaceKHR object for a window.
		 * 
		 * \param instance: The instance the create the surface from
		 * \param window: The window to create the surface from
		 * \return: A new surface object
		 */
		static SurfaceKHR create(Instance& instance, const IWindow& window);

		operator vk::SurfaceKHR() const;

	private:
		explicit SurfaceKHR(vk::raii::SurfaceKHR surface);
		
		vk::raii::SurfaceKHR m_Surface;
	};
}
