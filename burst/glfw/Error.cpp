#include "Error.h"

#include "GLFW/glfw3.h"

burst::glfw::GlfwError::GlfwError(const std::string& message) 
	: burst::RuntimeError(message)
{}

