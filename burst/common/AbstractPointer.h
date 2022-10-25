#pragma once

#include <functional>

#include "Types.h"
#include "Concepts.h"

namespace burst {
	template<Pointer T = void*>
	using DeleterFunction = std::function<void(T)>;
	
	/**
	 * The default deleter function.
	 */
	template<Pointer T>
	void default_deleter(void* pointer) {
		T typed = static_cast<T>(pointer);
		delete typed;
	}

	/**
	 * A raii class for storing pointers without knowing their original type.
	 * (Owns a pointer without knowing its original type)
	 */
	class AbstractPointer {
	public:
		AbstractPointer(void* pointer, DeleterFunction<> deleter);
		
		AbstractPointer(nullptr_t);
		AbstractPointer(const AbstractPointer&) = delete;
		AbstractPointer(AbstractPointer&&) noexcept;

		AbstractPointer& operator=(nullptr_t);
		AbstractPointer& operator=(const AbstractPointer&) = delete;
		AbstractPointer& operator=(AbstractPointer&&) noexcept;


		~AbstractPointer();

		/**
		 * Returns the contents of the abtract pointer as a type.
		 */
		template<Pointer P>
		const P as() const {
			return static_cast<P>(m_Pointer);
		}

		/**
		 * Returns the contents of the abstract pointer as a type.
		 */
		template<Pointer P>
		P as() {
			return static_cast<P>(m_Pointer);
		}

		/**
		 * Returns true if the pointer is occupied.
		 */
		bool occupied() const;

	private:
		void free();

		void* m_Pointer;
		DeleterFunction<> m_Deleter;
	};

	template<Pointer T, typename D = DeleterFunction<>>
	AbstractPointer abstract(T pointer, D deleter = default_deleter<T>) {
		return AbstractPointer(
			pointer,
			deleter
		);
	}
}
