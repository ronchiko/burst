#include "ImageView.h"

#include "../Instance/Device/Device.h"

namespace burst::vulkan {
	ImageView::ImageView(Device& device, IImage& image)
		: ImageView(image.create_view(device), image.dimensions())
	{}

	const Dimensions& ImageView::dimensions() const {
		return m_Dimensions;
	}

	ImageView::operator vk::ImageView() const {
		return *m_ImageView;
	}

	ImageView::ImageView(vk::raii::ImageView image_view, const Dimensions& dimensions)
		: m_ImageView(std::move(image_view))
		, m_Dimensions(dimensions)
	{}
}
