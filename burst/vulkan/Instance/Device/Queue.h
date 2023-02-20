#pragma once

#include <vulkan/vulkan.hpp>

#include <burst/common/Types.h>

namespace burst::vulkan {

	class Fence;
	class Semaphore;

	class SwapchainKHR;
	class CommandBuffer;

	class Queue
	{
	public:
		/**
		 * The device queue object.
		 *
		 * \param queue: The vulkan queue object
		 */
		explicit Queue(vk::Queue queue);

		/**
		 * Pushes a new stage to be submitted.
		 * 
		 * \param wait_on_semaphore: The semaphore to wait on
		 * \param stage: The stage to submit
		 */
		void push_stage(const Semaphore& wait_on_semaphore,
						vk::PipelineStageFlags stage);
		
		/**
		 * Submits all the pushed stages.
		 * 
		 * \param buffer: The buffer to submit
		 * \param signal_semaphore: The semaphore to single when submission is over
		 * \param in_flight_fence: The fence to wait on
		 */
		void sumbit(CommandBuffer& buffer,
					const Semaphore& signal_semaphore,
					const Fence& in_flight_fence);

		/**
		 * Presents this queue to a single swapchain.
		 * 
		 * \param wait_on: The semaphore to wait on
		 * \param swapchain: The swapchain to present to
		 * \param image_index: The index of the framebuffer to present
		 */
		void present(const Semaphore& wait_on, SwapchainKHR& swapchain, u32 image_index);

	private:
		struct SubmissionContext
		{
			constexpr static u32 RESERVED_CONTEXT_SIZE = 5;

			Vector<vk::Semaphore> semaphores;
			Vector<vk::PipelineStageFlags> stages;
		
			inline void enqueue(vk::Semaphore semaphore, vk::PipelineStageFlags stage) {
				semaphores.push_back(semaphore);
				stages.push_back(stage);
			}

			inline void flush() {
				semaphores.clear();
				stages.clear();
			}

			explicit SubmissionContext()
				: semaphores()
				, stages()
			{
				semaphores.reserve(RESERVED_CONTEXT_SIZE);
				stages.reserve(RESERVED_CONTEXT_SIZE);
			}

		} m_Submission;


		vk::Queue m_Queue;
	};
}
