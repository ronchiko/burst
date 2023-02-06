#pragma once

#include <vulkan/vulkan_raii.hpp>

#include "../Instance/Device/Device.h"

namespace burst::vulkan {

	constexpr u64 TIMEOUT_MAX = UINT64_MAX;

	/**
	 * Vulkan fence object.
	 */
	class Fence
	{
	public:
		/**
		 * Creates a new fence for a device.
		 * 
		 * \param owner: The owner of the device
		 * \param signaled: Should the fence start signaled
		 */
		explicit Fence(Device& owner, bool signaled = true);

		/**
		 * Waits for the fence to be signaled.
		 * 
		 * \param timeout: The max time to wait for the fence
		 * 
		 * \return true if the completion reason isn't timeout
		 */
		bool wait(u64 timeout = TIMEOUT_MAX) const;

		/**
		 * Reset the fence.
		 */
		void reset();

		/**
		 * Waits for a collection of fences to be signaled.
		 * 
		 * \param fences: The fences to wait for
		 * \param wait_all: Wait for all fences
		 * \param timeout: The timeout to wait for
		 * \return 
		 */
		static bool wait_many(
			const std::vector<std::reference_wrapper<Fence>>& fences,
			bool wait_all,
			u64 timeout = TIMEOUT_MAX);

		operator vk::Fence() const;

	private:
		vk::raii::Fence m_Fence;
		Device& m_Device;
	};

}
