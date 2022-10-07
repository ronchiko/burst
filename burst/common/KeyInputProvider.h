#pragma once

#include "Input.h"

namespace burst::input {
	class KeyInputProvider {
	public:
		virtual ~KeyInputProvider() = default;
	
		/**
		 * Checks if key is being pressed
		 */
		virtual bool is_pressed(Key) = 0;
		
		/**
		 * Checks if a key is being held
		 */
		virtual bool is_held(Key) = 0;

		/**
		 * Checks if key is being released
		 */
		virtual bool is_released(Key) = 0;
	};
}
