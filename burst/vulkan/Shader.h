#pragma once

#include <vulkan/vulkan.hpp>
#include <vulkan/vulkan_raii.hpp>

#include <burst/Common.h>

namespace burst::vulkan {
	using ShaderModule = vk::raii::ShaderModule;

	/**
	 * Loads a shader from a buffer.
	 */
	ShaderModule load_shader_from_buffer(const std::vector<burst::u8>& buffer);

	
}
