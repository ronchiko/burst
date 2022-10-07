#pragma once

#include "Types.h"
#include "Concepts.h"

namespace burst {
	template<typename T>
	class AbstractPointer {
	public:
		AbstractPointer(T pointer)
			: m_Pointer(pointer)
		{}

		AbstractPointer(const AbstractPointer&) = delete;
		AbstractPointer& operator=(const AbstractPointer&) = delete;

		AbstractPointer(AbstractPointer&& other) noexcept
			: m_Pointer(other.m_Pointer) {
			other.m_Pointer = nullptr;
		}

		AbstractPointer& operator=(AbstractPointer&& other) noexcept {
			m_Pointer = other.m_Pointer;
			other.m_Pointer = nullptr;

			return *this;
		}

		~AbstractPointer() {
			try {
				release();
			}
			catch (const std::exception&) {}
		}

		AbstractPointer(nullptr_t)
			: m_Pointer(nullptr)
		{}

		AbstractPointer& operator=(nullptr_t) {
			release();
		}

	private:
		void release() {
			if (nullptr != m_Pointer) {
				delete m_Pointer;
				m_Pointer = nullptr;
			}
		}


		T m_Pointer;
	};
}
