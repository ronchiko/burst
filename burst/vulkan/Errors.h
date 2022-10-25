#pragma once

#include <burst/common/Error.h>
#include <burst/common/Runtime.h>

namespace burst::vulkan {
	class InstanceComponentNotFound : public RuntimeError {
	public:
		explicit InstanceComponentNotFound(size_t hash);

		explicit InstanceComponentNotFound(const std::string& name);
	};

	/**
	 * When one or more required components are missing.
	 */
	class MissingRequiredComponentsError : public StaticError {
	public:
		MissingRequiredComponentsError();

		MissingRequiredComponentsError(cstr message);
	};

	/**
	 * When one or more required layers are missing.
	 */
	class MissingRequiredLayersError : public StaticError {
	public:
		MissingRequiredLayersError();
	};

	/**
	 * When no GPU can be used to run the game.
	 */
	class NoSuitableGpuError : public StaticError {
	public:
		NoSuitableGpuError();
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

	class ComponentNotFoundError : public RuntimeError {
	public:
		ComponentNotFoundError(const cstr name);

		template<typename T>
		constexpr static ComponentNotFoundError from() {
			return ComponentNotFoundError(burst::name<T>());
		}
	};
}
