#include "SwapchainImage.h"

#include "../Device/Device.h"

namespace burst::vulkan {
	constexpr vk::ComponentMapping IDENTITY = {
		vk::ComponentSwizzle::eIdentity,
		vk::ComponentSwizzle::eIdentity,
		vk::ComponentSwizzle::eIdentity,
		vk::ComponentSwizzle::eIdentity,
	};

	SwapchainImage::SwapchainImage(vk::Image image, vk::SurfaceFormatKHR format, Uint2 size)
		: m_Image(image)
		, m_Format(format)
		, m_Size(size.x, size.y)
	{}

	vk::raii::ImageView SwapchainImage::create_view(Device& device)
	{
		const vk::ImageViewCreateInfo create_info{
			vk::ImageViewCreateFlags(),
			m_Image,
			vk::ImageViewType::e2D,
			m_Format.format,
			IDENTITY,
			vk::ImageSubresourceRange{
				vk::ImageAspectFlagBits::eColor,
				/** base_mip_level = */ 0,
				/** level_count = */ 1,
				/** base_array_layer = */ 0,
				/** layer_count = */ 1
			}
		};

		return static_cast<vk::raii::Device&>(device).createImageView(create_info);
	}

	Dimensions SwapchainImage::dimensions() const {
		return Dimensions(m_Size.x, m_Size.y);
	}
}
