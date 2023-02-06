//#pragma once
//
//
//#include <vulkan/vulkan_raii.hpp>
//
//#include "Device.h"
//#include "SwapchainKHR.h"
//#include "Pipeline.h"
//
//namespace burst::vulkan {
//	/**
//	 * A singular frame buffer.
//	 */
//	class Framebuffer final {
//	public:
//		Framebuffer(nullptr_t);
//
//		Framebuffer(vk::raii::Framebuffer framebuffer, vk::Extent2D extent);
//
//		/**
//		 * Creates a new framebuffer from a device with a swapchain.
//		 * 
//		 * \param device: A device with a SwapchainKHR component
//		 * \param pipeline: The pipeline to create buffers into
//		 * \return 
//		 */
//		static Vector<Framebuffer> create(
//			const Device& device,
//			const Pipeline& pipeline
//		);
//
//		operator vk::Framebuffer() const;
//
//		vk::Extent2D extent() const;
//
//	private:
//		vk::raii::Framebuffer m_Framebuffer;
//		vk::Extent2D m_Extent;
//	};
//
//	class Framebuffers final
//	{
//	public:
//		explicit Framebuffers(Device& swapchain, const Pipeline& pipeline);
//
//		Framebuffer& operator[](u32 index);
//
//		/**
//		 * The extent of each frame.
//		 * 
//		 * \see SwapchainKHR::extent
//		 */
//		vk::Extent2D extent() const;
//
//	private:
//		SwapchainKHR& m_Swapchain;
//		Vector<Framebuffer> m_Framebuffers;
//	};
//}