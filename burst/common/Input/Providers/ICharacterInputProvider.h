#pragma once

#include <Burst/Common/Input/Input.h>

namespace burst::input {
	/**
	 * Provides input for text input,
	 * takes into consideration the state space
	 */
	class ICharacterInputProvider {
	public:
		IFACE_DESTRUCTOR(ICharacterInputProvider);

		/**
		 * Gets the next awaited character
		 */
		IFACE_FUNC(int next());

		/**
		 * Returns true if there is more characters to be consumed
		 */
		IFACE_FUNC(bool has_next());

		/**
		 * Flushes the rest of the characters in the provider
		 */
		IFACE_FUNC(void flush());
	};
}
