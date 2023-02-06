#pragma once

#include <vulkan/vulkan_raii.hpp>

#include "IImage.h"

namespace burst::vulkan {
	class Device;

	/**
	 * Represents a view onto an IImage object.
	 */
	class ImageView
	{
	public:
		explicit ImageView(Device& device, IImage& image);

		/**
		 * The dimensions of the image view.
		 * 
		 * \return 
		 */
		const Dimensions& dimensions() const;

		/**
		 * Convertor to vk::ImageView.
		 * 
		 * \return 
		 */
		operator vk::ImageView() const;

	private:
		explicit ImageView(vk::raii::ImageView image_view, const Dimensions& dimensions);
		
		vk::raii::ImageView m_ImageView;
		Dimensions m_Dimensions;
	};
}
