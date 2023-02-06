#include "Requirement.h"

#include <ranges>

namespace burst::vulkan {
	Vector<cstr> select_requirements(const Vector<Requirement>& source,
											RequirementType type)
	{
		using namespace std::views;

		auto result =
			source |
			filter([type](const Requirement& r) { return r.type == type; }) |
			transform([](const Requirement& r) { return r.value.c_str(); });

		return iter_convert<Vector<cstr>>(Set<cstr>(result.begin(), result.end()));
	}
}
