#include "AbstractPointer.h"

#include "Log.h"

namespace burst {
	AbstractPointer::AbstractPointer(void* pointer, DeleterFunction<> deleter)
		: m_Pointer(pointer), m_Deleter(deleter) {}

	AbstractPointer::AbstractPointer(nullptr_t)
		: m_Pointer(nullptr), m_Deleter(nullptr) {}

	AbstractPointer::AbstractPointer(AbstractPointer&& other) noexcept
		: m_Pointer(other.m_Pointer), m_Deleter(other.m_Deleter) {
		other = nullptr;
	}

	AbstractPointer& AbstractPointer::operator=(nullptr_t) {
		_free();
		m_Pointer = nullptr;

		return *this;
	}

	AbstractPointer& AbstractPointer::operator=(AbstractPointer&& other) noexcept {
		_free();
		m_Pointer = other.m_Pointer;
		m_Deleter = other.m_Deleter;
	
		other = nullptr;
		return *this;
	}

	AbstractPointer::~AbstractPointer() {
		try {
			_free();
		} catch(...) {}
	}

	bool AbstractPointer::occupied() const {
		return m_Pointer != nullptr;
	}

	void AbstractPointer::_free() {
		if (m_Pointer) {
			if (nullptr == m_Deleter) {
				burst::log::warning("Couldn't delete abstract pointer, because there wasn't a deleter");
				return;
			}

			m_Deleter(m_Pointer);
		}
	}
};
