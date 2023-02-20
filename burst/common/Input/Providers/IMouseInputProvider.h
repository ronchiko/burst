#pragma once

#include <Burst/Common/Input/Input.h>

namespace burst::input {
	/**
	 * Interface for mouse input providers.
	 */
	class IMouseInputProvider {
	public:
		virtual ~IMouseInputProvider() = default;

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
