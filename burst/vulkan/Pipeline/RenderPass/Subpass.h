#pragma once

#include <vulkan/vulkan.hpp>

#include <burst/Common.h>

namespace burst::vulkan {

	class Subpass
	{
	public:
		/**
		 * Describes what kind of subpass this is.
		 */
		enum class Type
		{
			Graphics = static_cast<u32>(vk::PipelineBindPoint::eGraphics),
			Compute = static_cast<u32>(vk::PipelineBindPoint::eCompute)
		};

		/**
		 * Creates a new subpass.
		 *
		 * \param type: The type of subpass this is
		 * \param inputs: The input references to this subpass
		 * \param outputs: The output references to this subpass
		 */
		explicit Subpass(Type type,
						 Vector<vk::AttachmentReference> inputs,
						 Vector<vk::AttachmentReference> outputs);

		/**
		 * Convertion operator to subpass description.
		 */
		operator vk::SubpassDescription() const;

	private:
		Type m_Type;
		Vector<vk::AttachmentReference> m_Outputs;
		Vector<vk::AttachmentReference> m_Inputs;

		vk::SubpassDescription m_Description;
	};
}
