#pragma once

#include <memory>
#include <vector>

#include <vulkan/vulkan.h>
#include <vulkan/vulkan_raii.hpp>

#include <burst/common/Window.h>


#include "InstanceComponent.h"

namespace burst::vulkan {

	class DebugMessenger : public IInstanceComponent {
	public:
		DebugMessenger() = default;

		virtual void add_requirements(InstanceRequirements&) const override;

		virtual void init(
			const vk::raii::Instance& instance, 
			const AdditionalCreateInfo& info
		) override;

	private:
		vk::raii::DebugUtilsMessengerEXT m_Messenger = nullptr;
	};
}
