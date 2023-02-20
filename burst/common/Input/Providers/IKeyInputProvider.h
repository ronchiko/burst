#pragma once

#include <Burst/Common/Input/Input.h>

namespace burst::input {
	class IKeyInputProvider {
	public:
		virtual ~IKeyInputProvider() = default;
	
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
