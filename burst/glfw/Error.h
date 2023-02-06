#pragma once

#include <burst/common/Types.h>
#include <burst/common/Error.h>

namespace burst::glfw {
	
	class GlfwError : public burst::RuntimeError {
	public:
		GlfwError(const std::string&);
	};
}
