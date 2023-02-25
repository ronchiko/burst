#include "SurfaceKHR.h"

#include <burst/common/Log.h>

/**
 * Procedure declaration for the create_surface method.
 * For each OS this method needs to be implemented, it should follow this
 * declaration.
 */
static vk::raii::SurfaceKHR create_surface(burst::vulkan::Instance&,
										   const burst::IWindow& window);

#ifdef _WIN32
#include "SurfaceKHR.Win32.inl"
#else
#error SurfaceKHR doesnt support this operating system
#endif

namespace burst::vulkan {
	SurfaceKHR::SurfaceKHR(vk::raii::SurfaceKHR surface)
		: m_Surface(::std::move(surface))
	{}

	SurfaceKHR SurfaceKHR::create(Instance& instance, const IWindow& window)
	{
		auto surface = create_surface(instance, window);

		log::debug("Loaded surfaceKHR object successfully");
		return SurfaceKHR(::std::move(surface));
	}

	SurfaceKHR::operator vk::SurfaceKHR() const {
		return *m_Surface;
	}
}
