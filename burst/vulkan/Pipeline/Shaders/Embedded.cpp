#include "Embedded.h"

namespace burst::vulkan {
	Unique<BuiltinShader> g_DefaultVertexShader = std::make_unique<BuiltinShader>(
		VERTEX_SHADER_DATA_BUFFER, Shader::Type::Vertex);
	
	Unique<BuiltinShader> g_DefaultFragmentShader = std::make_unique<BuiltinShader>(
		FRAGMENT_SHADER_DATA_BUFFER, Shader::Type::Fragment);

}
