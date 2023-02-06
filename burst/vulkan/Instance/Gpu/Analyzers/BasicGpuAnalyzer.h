#pragma once

#include "../IGpuAnalyzer.h"

namespace burst::vulkan::analyzers {

	/**
	 * A basic, non configurable gpu analyzer (for rendering).
	 */
	class BasicGpuAnalyzer : public IGpuAnalyzer
	{
	public:
		virtual Score rate(const Gpu& gpu) override;
	};
}
