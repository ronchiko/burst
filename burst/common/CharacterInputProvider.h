#pragma once

namespace burst::input {
	/**
	 * Provides input for text input,
	 * takes into consideration the state space
	 */
	class CharacterInputProvider {
	public:
		virtual ~CharacterInputProvider() = default;

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
