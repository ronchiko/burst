#pragma once

#include "Component.h"
#include "AbstractComponent.h"
#include "Errors.h"

namespace burst::vulkan {

	class ComponentList {
	public:
		ComponentList();

		/**
		 * Attempts to get component using its type
		 */
		template<Component C>
		C::Type::pointer get() {
			try {
				size_t hash = typeid(typename C::Type::pointer).hash_code();

				return reinterpret_cast<C::Type::pointer>(get(hash).component());
			}
			catch (const InstanceComponentNotFound&) {
				throw InstanceComponentNotFound(typeid(C).name());
			}
		}

		/**
		 * Pushes a component to the list.
		 */
		template<Component C>
		void push_back(C::Type::pointer c) {
			m_Components.push_back(AbstractComponent::make(c));
		}

	private:
		AbstractComponent& get(size_t hash);

		std::vector<AbstractComponent> m_Components;
	};
}
