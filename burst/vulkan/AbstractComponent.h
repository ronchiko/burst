#pragma once

#include <typeinfo>

#include "Component.h"

namespace burst::vulkan {

	class AbstractComponent {
	public:
		template<typename C>
		static AbstractComponent make(C& type) {
			return AbstractComponent{
				typeid(C).hash_code(),
				reinterpret_cast<void*>(type)
			};
		}

		/**
		 * Checks if this component is of a type
		 */
		template<Component C>
		bool is_type() const {
			if (nullptr == m_AbstractType) {
				return false;
			}

			return typeid(C::Type).hash_code() == m_Hash;
		}

		/**
		 * Gets a raw pointer to the abstracted component
		 */
		void* component();

		/**
		 * The hash of the components type.
		 */
		size_t hash() const;

	private:
		AbstractComponent(size_t hash, void* pointer);

		size_t m_Hash = -1;
		void* m_AbstractType = nullptr;
	};
}
