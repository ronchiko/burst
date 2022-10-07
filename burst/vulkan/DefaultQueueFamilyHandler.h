#pragma once

#include "QueueFamilyHandler.h"

namespace burst::vulkan {
	/**
	 * The default queue family handler
	 */
	class DefaultQueueFamilyHandler final : public QueueFamilyHandler {
	public:
		virtual void handle_queue_family(const QueueFamilyInfo& info) override;

		virtual bool is_complete() const override;

		virtual std::optional<u32> get_known_family(QueueFamilyType family) const;

		virtual std::vector< VkDeviceQueueCreateInfo> create_queue_creation_infos() const override;

	private:
		std::optional<u32> m_GraphicsFamily;
		std::optional<u32> m_PresentFamily;
	};
}
