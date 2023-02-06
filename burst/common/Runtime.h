#pragma once

#include <typeinfo>

#include "Types.h"

namespace burst {
	/**
	 * Gets the id of a class.
	 */
	template<class T>
	constexpr uid id()
	{
		return typeid(T).hash_code();
	}

	/** 
	 * Gets the name of the class
	 */
	template<class T>
	constexpr const cstr name()
	{
		return typeid(T).name();
	}
}
