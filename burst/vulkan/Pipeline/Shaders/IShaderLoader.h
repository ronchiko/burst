#pragma once

#include "Shader.h"

namespace burst::vulkan {
	class Device;

	/**
	 * An interface for linking shaders.
	 */
	class IShaderLoader
	{
	public:
		virtual ~IShaderLoader() = default;

		/**
		 * Loads the shader.
		 * 
		 * \param device: The device to load the shader into
		 */ 
		virtual Shader load(burst::vulkan::Device& device) const = 0;
	};
}


