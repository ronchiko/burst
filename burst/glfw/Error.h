#pragma once

#include "burst/common/Types.h"
#include "burst/common/Error.h"

namespace burst::glfw {
	
	class Error : public burst::RuntimeError {
	public:
		Error(const std::string&, burst::u32 error);
	
	private:
		burst::u32 m_ErrorCode;
	};
}
