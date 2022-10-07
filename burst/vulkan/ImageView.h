#pragma once

#include <vulkan/vulkan.h>

namespace burst::vulkan {
	class ImageView final {
	public:
		ImageView(VkDevice device, VkImage image, VkFormat format);

		ImageView(ImageView&&) noexcept;
		ImageView& operator=(ImageView&&) noexcept;

		ImageView(const ImageView&) = delete;
		ImageView& operator=(const ImageView&) = delete;

		~ImageView();

	private:
		void release();


		VkImageView m_View = nullptr;
		VkDevice m_Device = nullptr;
	};
}
