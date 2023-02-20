#include "Pipeline.h"

#include "../Instance/Device/Device.h"
#include "../Instance/SwapchainKHR/SwapchainKHR.h"

#include "Shaders/IShaderLoader.h"

#include "PipelineLoader.h"

namespace burst::vulkan {

	Pipeline Pipeline::create(burst::vulkan::Device& device,
							  burst::vulkan::SwapchainKHR& swapchain,
							  const Configuration& configuration)
	{
		PipelineLoader loader(device, swapchain, configuration);

		return loader.create();
	}

	const RenderPass& Pipeline::render_pass() const
	{
		return m_RenderPass;
	}

	RenderPass& Pipeline::render_pass()
	{
		return m_RenderPass;
	}

	Pipeline::operator vk::Pipeline() const
	{
		return *m_Pipeline;
	}

	Pipeline::Pipeline(vk::raii::Pipeline pipeline,
					   RenderPass render_pass,
					   vk::raii::PipelineLayout layout,
					   Data data)
		: m_Pipeline(std::move(pipeline))
		, m_RenderPass(std::move(render_pass))
		, m_Layout(std::move(layout))
		, m_Data(std::move(data))
	{
	}
}
