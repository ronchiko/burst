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

		options.capabilities = m_Gpu.m_Device.getSurfaceCapabilitiesKHR(m_Surface);
		options.formats = m_Gpu.m_Device.getSurfaceFormatsKHR(m_Surface);
		options.present_modes = m_Gpu.m_Device.getSurfacePresentModesKHR(m_Surface);

		return options;
	}

	bool GpuSurfaceBinding::does_surface_support_khr(u32 index) {
		return m_Gpu.m_Device.getSurfaceSupportKHR(index, m_Surface);
	}
}
