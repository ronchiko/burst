#pragma once

#include <vulkan/vulkan_raii.hpp>

#include "../../Gfx/IImage.h"

namespace burst::vulkan {
	/**
	 * An image taken from a swapchain.
	 */
	class SwapchainImage : public IImage
	{
	public:
		explicit SwapchainImage(vk::Image image, vk::SurfaceFormatKHR format, Uint2 size);

		inline virtual operator vk::Image() const override
		{
			return m_Image;
		}

		virtual vk::raii::ImageView create_view(Device& device) override;

		virtual Dimensions dimensions() const override;

	private:
		vk::Image m_Image;
		vk::SurfaceFormatKHR m_Format;
		Uint2 m_Size;
	};
}
