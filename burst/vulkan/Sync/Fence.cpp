#include "Fence.h"

#include "Errors.h"

namespace burst::vulkan {

	static vk::raii::Fence create_fence(Device& owner, bool signaled)
	{
		vk::FenceCreateInfo create_info{
			signaled ? vk::FenceCreateFlagBits::eSignaled
					 : static_cast<vk::FenceCreateFlagBits>(0)
		};

		return vk::raii::Fence(static_cast<vk::raii::Device&>(owner), create_info);
	}

	Fence::Fence(Device& owner, bool signaled)
		: m_Fence(create_fence(owner, signaled))
		, m_Device(owner)
	{}

	bool Fence::wait(u64 timeout) const
	{
		auto result = static_cast<vk::Device>(m_Device).waitForFences(
			{ *m_Fence }, true, timeout);
		if(vk::Result::eSuccess != result && vk::Result::eTimeout != result) {
			throw VulkanError("Failed to wait on fence", result);
		}

		return vk::Result::eTimeout != result;
	}

	void Fence::reset()
	{
		static_cast<vk::Device>(m_Device).resetFences({ *m_Fence });
	}

	bool Fence::wait_many(const std::vector<std::reference_wrapper<Fence>>& fences,
						  bool wait_all,
						  u64 timeout)
	{
		if(fences.empty()) {
			return true;
		}

		Device& owner = fences[0].get().m_Device;

		std::vector<vk::Fence> vulkan_fences(fences.size());
		std::transform(fences.begin(),
					   fences.end(),
					   vulkan_fences.begin(),
					   [&owner](const auto& fence) {
						   if(&fence.get().m_Device != &owner) {
							   throw RuntimeError::make(
								   "Can't wait for fences with diffenrent owner!");
						   }
						   return *fence.get().m_Fence;
					   });

		static_cast<vk::Device>(owner).waitForFences(
			vulkan_fences, wait_all, timeout);
	}

	Fence::operator vk::Fence() const
	{
		return *m_Fence;
	}
}
