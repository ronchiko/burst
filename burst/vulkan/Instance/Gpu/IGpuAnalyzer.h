#pragma once

#include <burst/Common.h>

#include "Gpu.h"

namespace burst::vulkan {
	
	class Gpu;

	/**
	 * An interface for rating gpus.
	 */
	class IGpuAnalyzer
	{
	public:
		using Score = u32;

		/// The score to when the gpu is reject 
		/// And is not considered a valid GPU
		static constexpr Score REJECT_GPU = 0;


		IFACE_DESTRUCTOR(IGpuAnalyzer);

		/**
		 * Rates a GPU.
		 * 
		 * \param gpu: The gpu to score
		 */
		IFACE_FUNC(Score rate(const Gpu& gpu));
	};
}
