#pragma once

#include <burst/Common/Types.h>

namespace burst::vulkan {
	/**
	 * The possible requirement types.
	 */
	enum class RequirementType{
		InstanceExtension,
		DeviceExtension,
		ValidationLayer,
	};

	/**
	 * A requirement.
	 */
	struct Requirement
	{
		// The type of the requirement
		RequirementType type;
		// The requirement value
		String value;
	};

	/**
	 * Selects requirements of type from the a requirements array.
	 *
	 * \param source: The source array to select from
	 * \param type: The type of the array
	 */
	Vector<cstr> select_requirements(const Vector<Requirement>& source,
									 RequirementType type);
}
