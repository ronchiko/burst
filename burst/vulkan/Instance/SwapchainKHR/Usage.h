#pragma once

#include <vulkan/vulkan.hpp>

#include <burst/Common.h>

namespace burst::vulkan {
	enum class ImageUsage
	{
		AttachColor = static_cast<u32>(VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT),
		Trasfer = static_cast<u32>(VK_IMAGE_USAGE_TRANSFER_DST_BIT)
	};

	enum class CompositeAlpha
	{
		Opaque = static_cast<u32>(VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR),
		Inherit = static_cast<u32>(VK_COMPOSITE_ALPHA_INHERIT_BIT_KHR)
	};
}
