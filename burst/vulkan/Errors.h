#pragma once

#include <burst/common/Error.h>

namespace burst::vulkan {
	class InstanceComponentNotFound : public RuntimeError {
	public:
		explicit InstanceComponentNotFound(size_t hash);

		explicit InstanceComponentNotFound(const std::string& name);
	};

	/**
	 * Thrown when a component can't initialize themselfs, and want to wait for a later 
	 * initialization iteration (usually when waiting for logical/physical devices)
	 */
	class WaitingForLaterInitialization : public StaticError {
	public:
		WaitingForLaterInitialization();
	};

	/**
	 * When an instance is not fully initialized after completing its creation
	 */
	class InstanceNotFullyInitialized : public StaticError {
	public:
		InstanceNotFullyInitialized();
	};
}
