#pragma once

#include <vector>
#include <memory>

#include "IInstanceDependent.h"

namespace burst::vulkan {

	template<typename... T>
	struct InstanceComponentList;

	template<>
	struct InstanceComponentList<> {
	protected:
		static void _get_components_recursively(InstanceComponentVector& vector)
		{}
	};

	template<typename T, typename... Rest>
	struct InstanceComponentList<T, Rest...>
		: private InstanceComponentList<Rest...>
	{
	public:
		static InstanceComponentVector vector() {
			InstanceComponentVector vector;
			vector.reserve(sizeof...(Rest) + 1);
			_get_components_recursively(vector);

			return vector;
		}

	private:
		using Base = InstanceComponentList<Rest...>;

	protected:
		
		static void _get_components_recursively(InstanceComponentVector& vector) {
			vector.push_back(std::make_unique<T>());
			Base::_get_components_recursively(vector);
		}
	};


}
