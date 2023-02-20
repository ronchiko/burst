#pragma once

#include "../../Types.h"

#include "../../Concepts.h"

namespace burst {

	/**
	 * A behavior class that allows access an class with the '[]' operator
	 * using a type which is castable to u32.
	 * 
	 * \tparam Enum: The enum type to be able to access from
	 * \tparam Base: The base type to add this functionality to
	 */
	template<burst::castable<u32> E, burst::accessable<u32> Base >
	class EnumAccess : public Base
	{
	public:
		static_assert(!std::is_same_v<E, u32>, "Enum type cant be u32");

		using Base::operator[]; // Used to inherit the base [] operator
		using Base::at;

		EnumAccess(Base base)
			: Base(::std::move(base))
		{}

		inline const auto& operator[](const E& value) const
		{
			return this->Base::operator[](static_cast<u32>(value));
		}

		inline const auto& at(const E& value) const {
			return this->Base::operator[](static_cast<u32>(value));
		}
	};

	/**
	 * Same as EnumAccess but allows modification of the 
	 * accessed value.
	 * 
	 * \see EnumAccess
	 */
	template<burst::castable<u32> E, burst::accessable<u32> Base>
	class MutableEnumAccess : public EnumAccess<E, Base>
	{
	public:
		using Base::operator[]; // Used to inherit the base [] operator

		MutableEnumAccess(Base base)
			: EnumAccess<E, Base>(::std::move(base))
		{}

		inline auto& operator[](const E& value)
		{
			return this->Base::operator[](static_cast<u32>(value));
		}
	};
}
