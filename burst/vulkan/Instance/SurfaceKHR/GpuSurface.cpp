#include "GpuSurface.h"

#include "SurfaceSupportOptions.h"

namespace burst::vulkan {
	GpuSurfaceBinding::GpuSurfaceBinding(const SurfaceKHR& surface, const Gpu& gpu)
		: m_Surface(surface)
		, m_Gpu(gpu)
	{}

	SurfaceSupportOptions GpuSurfaceBinding::get_surface_support_options()
	{
		SurfaceSupportOptions options{};

		options.capabilities = _gpu().m_Device.getSurfaceCapabilitiesKHR(_surface());
		options.formats = _gpu().m_Device.getSurfaceFormatsKHR(_surface());
		options.present_modes = _gpu().m_Device.getSurfacePresentModesKHR(_surface());

		return options;
	}

	bool GpuSurfaceBinding::does_surface_support_khr(u32 index) {
		return _gpu().m_Device.getSurfaceSupportKHR(index, _surface());
	}

	const SurfaceKHR& GpuSurfaceBinding::_surface() const {
		ASSERT(m_Surface.has_value(), "Binding surface not initialized!");
		
		return m_Surface.value();
	}

	const Gpu& GpuSurfaceBinding::_gpu() const
	{
		ASSERT(m_Gpu.has_value(), "Binding surface not initialized!");

		return m_Gpu.value();
	}
}
