#pragma once

#include <vulkan/vulkan_raii.hpp>

#include <burst/common/Types.h>

#include "Dimensions.h"

namespace burst::vulkan {

	class Device;

	/**
	 * Abstract representation of an image.
	 */
	class IImage
	{
	public:
		virtual ~IImage() = default;

		/**
		 * Convertion to vk::Image.
		 */
		virtual operator vk::Image() const = 0;

		/**
		 * Creates a view to the desired image.
		 */
		virtual vk::raii::ImageView create_view(Device&) = 0;

		/**
		 * The dimensions of this image.
		 */
		virtual Dimensions dimensions() const = 0;
	};
}
