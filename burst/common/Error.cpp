#include "Error.h"

namespace burst {

	RuntimeError::RuntimeError(const String& message)
		: std::runtime_error(message)
	{}

	StaticError::StaticError(cstr message)
		: std::exception(message)
	{}

	NullptrError::NullptrError(cstr message)
		: StaticError(message)
	{}

	FileNotFoundError::FileNotFoundError(const String& name)
		: RuntimeError(concat("File not found", name))
	{}
}
