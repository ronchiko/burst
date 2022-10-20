#pragma once

#include <set>

#include <burst/common/Types.h>
#include <burst/common/Window.h>

namespace burst::vulkan {
	/**
	 * The requirements for constructing an instance.
	 */
	struct InstanceRequirements {
		std::set<cstr> extensions;
		std::set<cstr> validation_layers;
		std::set<cstr> device_extensions;
	};

	/**
	 * Additional creation info.
	 */
	struct AdditionalCreateInfo {
		Window* window = nullptr;

		// For items to show up in the requirements section a components
		// must specify it wants them.
		const InstanceRequirements requirements = {};
	};

	/**
	 * A class thats required to have an impact on the requirements of the instance.
	 */
	INTERFACE IInstanceDependent{
	public:
		IFACE_DESTRUCTOR(IInstanceDependent);

		/**
		 * Each child class should state in this function what are the
		 * extensions/validation layers/device extensions it requires to work.
		 * 
		 * Then when initializing the component, it will be guranteed that each
		 * requirement is satesfied.
		 */
		IFACE_FUNC(void add_requirements(InstanceRequirements&) const);
	};

	using InstanceComponentVector = UniqueVector<IInstanceDependent>;

}
