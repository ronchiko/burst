#include "Error.h"

#include "GLFW/glfw3.h"

burst::glfw::Error::Error(const std::string& message, burst::u32 code) 
	: burst::RuntimeError(message)
	, m_ErrorCode(code)
{}

