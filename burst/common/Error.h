#pragma once

#include <stdexcept>

#include "Types.h"
#include "Meta.h"

namespace burst {
	using Error = std::exception;

	class RuntimeError : public std::runtime_error {
	public:
		explicit RuntimeError(const std::string& message);
	
		template<typename... T>
		static RuntimeError make(const T&... args) {
			return RuntimeError(burst::concat(args...));
		}
	};

	class StaticError : public Error {
	public:
		explicit StaticError(burst::cstr message);
	};
	
	class NullptrError : public StaticError {
	public:
		explicit NullptrError(burst::cstr message);
	};

	class FileNotFoundError : public RuntimeError {
	public:
		explicit FileNotFoundError(const std::string& name);
	};
}
