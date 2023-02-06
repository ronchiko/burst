#pragma once

#include <vulkan/vulkan.hpp>

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

	class ComponentNotFoundError : public RuntimeError {
	public:
		ComponentNotFoundError(const cstr name);

		template<typename T>
		constexpr static ComponentNotFoundError from() {
			return ComponentNotFoundError(burst::name<T>());
		}
	};

	class MissingRequiredQueueError : public StaticError {
	public:
		MissingRequiredQueueError();
	};

	class VulkanError : public RuntimeError
	{
	public:
		explicit VulkanError(const std::string& message, vk::Result result);
		explicit VulkanError(const std::string& message, VkResult result);
	};

	/**
	 * When cant create command pool.
	 */
	class FailedToCreateCommandPoolError : public StaticError
	{
	public:
		explicit FailedToCreateCommandPoolError(cstr msg); 
	};
}
