#include "BasicGpuAnalyzer.h"

namespace burst::vulkan::analyzers {

	constexpr u32 DISCRETE_GPU_SCORE_BOOST = 1000;
	
	IGpuAnalyzer::Score BasicGpuAnalyzer::rate(const Gpu& gpu) {
		Score score = 0;

		if (GpuType::Discrete == gpu.type()) {
			score += DISCRETE_GPU_SCORE_BOOST;
		}

		return score;
	}

}
