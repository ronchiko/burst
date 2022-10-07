#pragma once

#include <vulkan/vulkan.hpp>
#include <vulkan/vulkan_raii.hpp>

namespace burst::vulkan {
	using ShaderModule = vk::raii::ShaderModule;

	ShaderModule load_vertex_shader_module(const std::string& path);
	

}
