#pragma once

#include <vulkan/vulkan.hpp>

#include <burst/common/IRenderer.h>
#include <burst/common/Types/Address.h>

#include "Queues.h"

namespace burst::vulkan {

	class Gpu;
	class SurfaceKHR;

	/**
	 * Info about the scanned queue family.
	 */
	struct QueueFamilyProperties : public vk::QueueFamilyProperties
	{
	public:
		/**
		 * Creates a new queue family properties object.
		 *
		 * \param b: The base family properties
		 * \param index: The index of the family being processed
		 * \param gpu: The gpu the family came from
		 * \param surface[optional]: The surface of the gpu if present
		 */
		QueueFamilyProperties(const vk::QueueFamilyProperties& b,
							  u32 index,
							  Ref<const Gpu> gpu,
							  Address<SurfaceKHR> surface = nullptr)
			: vk::QueueFamilyProperties(b)
			, index(index)
			, gpu(gpu)
			, surface(surface)
		{}

		u32 index;					   // The index of the queue inspected
		Ref<const Gpu> gpu;			   // The gpu of this object
		Address<SurfaceKHR>& surface;  // The surface attached, might be unavailable
	};

	/**
	 * Inteface for classes that should find queues for a gpu.
	 */
	class IQueueLocator
	{
	public:
		/**
		 * The possible outcome when locating queues.
		 */
		enum Status
		{
			/**
			 * This status means the queue was successfuly added.
			 */
			Success,
			/**
			 * This status means the queue cannot be added right now
			 * because it requires a diffrent queue to exist and it
			 * doesnt yet.
			 */
			Postpone,
			/**
			 * Failed to add the queue and there is no point to try again.
			 */
			Failure
		};

		IFACE_DESTRUCTOR(IQueueLocator);

		/**
		 * Finds a the target queue and adds it to the queues struct
		 *
		 * \param properties: The properties of the queue object
		 * \param q: The queue struct to return the info to
		 *
		 * \returns: Status::Success, Status::Failure or Status::Postpone
		 */
		IFACE_FUNC(Status locate(const QueueFamilyProperties& properties,
								 Queues& q));
	};
}
