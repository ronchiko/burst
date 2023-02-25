#pragma once

#include <burst/common/Log.h>

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

		inline const SurfaceKHR& surface() const
		{
			return _surface();
		} 

	private:
		// Safe getters
		const SurfaceKHR& _surface() const;
		const Gpu& _gpu() const;

		Optional<Ref<const SurfaceKHR>> m_Surface;
		Optional<Ref<const Gpu>> m_Gpu;
	};
}
