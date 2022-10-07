#include "ImageView.h"

#include <stdexcept>

#include "Validation.h"

static VkImageView create_image_view(
	VkDevice device,
	VkImage image,
	VkFormat format
) {
	using burst::vulkan::NO_ALLOCATOR;

	VkImageViewCreateInfo info{};
	info.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
	info.image = image;
	info.viewType = VK_IMAGE_VIEW_TYPE_2D;
	info.format = format;
	info.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
	info.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
	info.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
	info.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
	info.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	info.subresourceRange.baseMipLevel = 0;
	info.subresourceRange.levelCount = 1;
	info.subresourceRange.baseArrayLayer = 0;
	info.subresourceRange.layerCount = 1;

	VkImageView view = nullptr;
	if (VK_SUCCESS != vkCreateImageView(device, &info, NO_ALLOCATOR, &view)) {
		throw burst::RuntimeError::make("Faile to create image view");
	}

	return view;
}

burst::vulkan::ImageView::ImageView(
	VkDevice device,
	VkImage image,
	VkFormat format
) : m_Device(device), m_View(create_image_view(device, image, format)) 
{}

burst::vulkan::ImageView::ImageView(ImageView&& other) noexcept 
	: m_Device(other.m_Device), m_View(other.m_View) {
	other.m_Device = nullptr;
	other.m_View = nullptr;
}

burst::vulkan::ImageView& burst::vulkan::ImageView::operator=(
	ImageView&& other
) noexcept {
	m_Device = other.m_Device;
	m_View = other.m_View;

	other.m_Device = nullptr;
	other.m_View = nullptr;

	return *this;
}

burst::vulkan::ImageView::~ImageView() {
	try {
		release();
	} catch(const std::exception&) {}
}

void burst::vulkan::ImageView::release() {
	if (nullptr != m_View) {
		vkDestroyImageView(m_Device, m_View, NO_ALLOCATOR);
	}
}
