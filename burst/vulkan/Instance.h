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
		using Map = std::unordered_map<u32, IComponent>;

		Instance(
			vk::raii::Instance instance,
			Map component,
			InstanceRequirements requirements
		);

		template<InstanceComponent IC>
		IC& get() {
			if (auto& component = m_Components.at(burst::id<IC>()); nullptr != component) {
				return *component;
			}

			throw ComponentNotFoundError::from<IC>();
		}

		/**
		 * Gets a component from this instance.
		 */
		template<InstanceComponent IC>
		const IC& get() const {
			if (auto& component = m_Components.at(burst::id<IC>()); nullptr != component) {
				return *component;
			}
			
			throw ComponentNotFoundError::from<IC>();
		}

		template<InstanceComponent IC>
		bool get(IC& ic) {
			if (auto& component = m_Components.at(burst::id<IC>()); nullptr != component) {
				ic = *component;
				return true;
			}

			return false;
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
	Instance make_instance(
		cstr name,
		u32 version,
		InstanceComponentVector& components,
		Window* window = nullptr
	);
}