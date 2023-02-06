#pragma once

#include "../Gpu/Gpu.h"
#include "SurfaceKHR.h"

namespace burst::vulkan {

	/**
	 * A binding between a GPU and a SurfaceKHR object.
	 */
	class GpuSurfaceBinding
	{
	public:
		/**
		 * Creates a gpu surface binding.
		 * 
		 * \param surface: The surface
		 * \param gpu: The gpu
		 */
		explicit GpuSurfaceBinding(const SurfaceKHR& surface, const Gpu& gpu);

		/**
		 * Gets the support information about a surface.
		 */
		SurfaceSupportOptions get_surface_support_options();

		/**
		 * Checks if a surface supports KHR.
		 *
		 * \param index: The queue index
		 */
		bool does_surface_support_khr(u32 index);

		constexpr const SurfaceKHR& surface() const
		{
			return m_Surface;
		} 

	private:
		const SurfaceKHR& m_Surface;
		const Gpu& m_Gpu;
	};
}
