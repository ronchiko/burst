#pragma once

#include "Input.h"

namespace burst::input {
	class MouseInputProvider {
	public:
		virtual ~MouseInputProvider() = default;

		/**
		 * Checks if mouse button is being pressed
		 */
		virtual bool is_pressed(MouseButton button) = 0;

		/**
		 * Checks if mouse button is being held
		 */
		virtual bool is_held(MouseButton button) = 0;

		/**
		 * Checks if mouse button is being released
		 */
		virtual bool is_released(MouseButton) = 0;
	};
}
