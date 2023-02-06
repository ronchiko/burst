#include "BuiltinShader.h"

namespace burst::vulkan {
	BuiltinShader::BuiltinShader(Buffer<char> buffer, Shader::Type type)
		: m_Buffer(buffer.ensure_ownership())
		, m_Type(type)
	{}

	Shader BuiltinShader::load(Device& device) const {
		return Shader::from_buffer(device, m_Buffer, m_Type);
	}
}
