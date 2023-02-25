#pragma once

#include <Burst/Common/Input/Input.h>

namespace burst::input {
	/**
	 * Provides input for text input,
	 * takes into consideration the state space
	 */
	class ICharacterInputProvider {
	public:
		virtual ~ICharacterInputProvider() = default;

		/**
		 * Gets the next awaited character
		 */
		virtual int next() = 0;

		/**
		 * Returns true if there is more characters to be consumed
		 */
		virtual bool has_next() = 0;

		/**
		 * Flushes the rest of the characters in the provider
		 */
		virtual void flush() = 0;
	};
}
