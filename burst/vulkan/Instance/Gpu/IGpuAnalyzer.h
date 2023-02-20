#pragma once

#include <burst/Common/Types.h>

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


		virtual ~IGpuAnalyzer() = default;

		/**
		 * Rates a GPU.
		 * 
		 * \param gpu: The gpu to score
		 */
		virtual Score rate(const Gpu& gpu) = 0;
	};
}
