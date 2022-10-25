#pragma once


#include <unordered_map>

#include <vulkan/vulkan_raii.hpp>

#include <burst/common/Meta.h>
#include <burst/common/Runtime.h>

#include "Errors.h"
#include "InstanceComponent.h"


namespace burst::vulkan {

	class Instance {
	public:
		using IComponent = std::unique_ptr<IInstanceComponent>;
		using Map = IdMap<IComponent>;

		Instance(
			vk::raii::Instance instance,
			Map component,
			InstanceRequirements requirements,
			const AdditionalCreateInfo& create_info
		);

		template<InstanceComponent IC>
		IC& get() {
			try {
				if (auto& component = m_Components.at(burst::id<IC>()); nullptr != component) {
					return *reinterpret_cast<IC*>(component.get());
				}
			}
			catch (const std::out_of_range&) {}

			throw ComponentNotFoundError::from<IC>();
		}

		/**
		 * Gets a component from this instance.
		 */
		template<InstanceComponent IC>
		const IC& get() const {
			return const_cast<Instance*>(this)->get<IC>();
		}

		const vk::raii::Instance& instance() const;

		const InstanceRequirements requirements() const;

	private:
		vk::raii::Instance m_Instance;
		Map m_Components;
		InstanceRequirements m_Requirements;
	};

	/**
	 * Creates a new instance
	 */
	std::pair<Instance, AdditionalCreateInfo> make_instance(
		cstr name,
		u32 version,
		InstanceComponentVector& components,
		Window* window = nullptr
	);
}