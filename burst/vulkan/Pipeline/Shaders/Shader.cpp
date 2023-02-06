#include "Shader.h"

#include "../../Instance/Device/Device.h"

namespace burst::vulkan {
	Shader::Shader()
		: Shader(nullptr)
	{}

	Shader::Shader(nullptr_t)
		: m_Shader(nullptr)
		, m_Type(Type::Vertex)
	{}

	Shader::Shader(vk::raii::ShaderModule shader, Type type)
		: m_Shader(std::move(shader))
		, m_Type(type)
	{}

	Shader::Shader(Shader&& other)
		: m_Shader(std::move(other.m_Shader))
		, m_Type(other.m_Type)
	{
		other.m_Shader = nullptr;
	}

	Shader& Shader::operator=(Shader&& other) {
		m_Shader = std::move(other.m_Shader);
		m_Type = other.m_Type;

		other.m_Shader = nullptr;

		return *this;
	}

	Shader
	Shader::from_buffer(Device& device, const Buffer<char>& buffer, Type type)
	{
		vk::ShaderModuleCreateInfo create_info(
			vk::ShaderModuleCreateFlags(),
			buffer.size(),
			reinterpret_cast<const uint32_t *>(buffer.data()),
			nullptr);

		return Shader(vk::raii::ShaderModule(static_cast<vk::raii::Device&>(device), create_info), type);
	}

	Shader::operator vk::ShaderModule() const
	{
		return *m_Shader;
	}

	Shader::Type Shader::type() const
	{
		return m_Type;
	}

	bool Shader::operator==(nullptr_t) const
	{
		return !(*m_Shader);
	}
}