#include "Error.h"

burst::RuntimeError::RuntimeError(const std::string& message)
	: std::runtime_error(message)
{}

burst::StaticError::StaticError(burst::cstr message)
	: std::exception(message)
{}

burst::NullptrError::NullptrError(burst::cstr message) 
	: StaticError(message)
{}
