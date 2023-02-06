#pragma once

#include <Burst/Common/Input/Input.h>

namespace burst::input {
	class IKeyInputProvider {
	public:
		IFACE_DESTRUCTOR(IKeyInputProvider);
	
		/**
		 * Checks if key is being pressed
		 */
		IFACE_FUNC(bool is_pressed(Key));
		
		/**
		 * Checks if a key is being held
		 */
		IFACE_FUNC(bool is_held(Key));

		/**
		 * Checks if key is being released
		 */
		IFACE_FUNC(bool is_released(Key));
	};
}
