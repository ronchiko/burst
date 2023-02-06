#pragma once

#include "../IShaderLoader.h"

#include <burst/common/Types/Buffer.h>

namespace burst::vulkan {
	/**
	 * Load a shader from a buffer.
	 */
	class BuiltinShader : public IShaderLoader
	{
	public:
		/**
		 * Create a new builtin shader loader.
		 * 
		 * \param buffer: The buffer of the shader
		 * \param type: The type of the shader
		 */
		BuiltinShader(Buffer<char> buffer, Shader::Type type);

		/**
		 * Loads the shader into a device.
		 */
		virtual Shader load(Device& device) const override;

	private:
		Buffer<char> m_Buffer;	// Keep a copy of the buffer for safety
		Shader::Type m_Type;
	};
}


