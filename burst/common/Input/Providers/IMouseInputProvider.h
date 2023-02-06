#pragma once

#include <Burst/Common/Input/Input.h>

namespace burst::input {
	/**
	 * Interface for mouse input providers.
	 */
	class IMouseInputProvider {
	public:
		IFACE_DESTRUCTOR(IMouseInputProvider);

		/**
		 * Checks if mouse button is being pressed
		 */
		IFACE_FUNC(bool is_pressed(MouseButton button));

		/**
		 * Checks if mouse button is being held
		 */
		IFACE_FUNC(bool is_held(MouseButton button));

		/**
		 * Checks if mouse button is being released
		 */
		IFACE_FUNC(bool is_released(MouseButton));
	};
}
