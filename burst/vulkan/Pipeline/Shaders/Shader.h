#pragma once

#include <vulkan/vulkan.hpp>
#include <vulkan/vulkan_raii.hpp>

#include <burst/Common/Types.h>
#include <burst/Common/Types/Buffer.h>

#include "../../Instance/Device/Device.h"

namespace burst::vulkan {

	constexpr const char* SHADER_DEFAULT_ENTRYPOINT = "main";

	/**
	 * The shader class.
	 */
	class Shader {
	public:
		/**
		 * The possible types of shaders.
		 */
		enum class Type {
			Vertex = static_cast<u32>(vk::ShaderStageFlagBits::eVertex),
			Fragment = static_cast<u32>(vk::ShaderStageFlagBits::eFragment),
			Compute = static_cast<u32>(vk::ShaderStageFlagBits::eCompute)
		};
		
		Shader();
		Shader(nullptr_t);

		Shader(Shader&& other);
		Shader& operator=(Shader&& other);

		Shader(const Shader&) = delete;
		Shader& operator=(const Shader&) = delete;

		~Shader() = default;

		/**
		 * Creates a new shader from a spir-v buffer.
		 * 
		 * \param device: The device to create the shader for
		 * \param buffer: The spir-v buffer
		 * \param type: The shader tpe
		 * \return 
		 */
		static Shader from_buffer(
			Device& device,
			const Buffer<char>& buffer,
			Type type
		);

		/**
		 * Convert to the vk::ShaderModule.
		 */
		explicit operator vk::ShaderModule() const;

		/**
		 * The type of the shader.
		 */
		Type type() const;

		/**
		 * Checks if this shader has a value.
		 */
		bool operator==(nullptr_t) const;

	private:

		/**
		 * Creates a new shader.
		 * 
		 * \param module: The vulkan shader module
		 * \param type: The type of the shader
		 */
		explicit Shader(vk::raii::ShaderModule module, Type type);

		vk::raii::ShaderModule m_Shader = nullptr;
		Type m_Type = Type::Vertex;
	};
	
}
