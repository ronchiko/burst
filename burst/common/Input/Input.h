#pragma once

#include <memory>

#include <Burst/Common/Types.h>

namespace burst::input {
	
	// Predeclare the provider interfaces
	class IKeyInputProvider;
	class IMouseInputProvider;
	class ICharacterInputProvider;

	/**
	 * The supported keys for burst.
	 */
	enum class Key {
		A,
		B,
		C,
		D,
		E,
		F,
		G,
		H,
		I,
		J,
		K,
		L,
		M,
		N,
		O,
		P,
		Q,
		R,
		S,
		T,
		U,
		V,
		W,
		X,
		Y,
		Z,
		Num0,
		Num1,
		Num2,
		Num3,
		Num4,
		Num5,
		Num6,
		Num7,
		Num8,
		Num9,
		Left,
		Right,
		Up,
		Down,
		Tab,
		Plus,
		Minus,
		Backspace,
		Enter,
		WinKey,
		Home,
		PageUp,
		PageDown,
		End,
		Insert,
		Delete,
		Tilda,
		Escape,
		Space,
		LeftShift,
		RightShift,
		LeftCtrl,
		RightCtrl,
		LeftAlt,
		RightAlt,
		Comma,
		Dot,
		Quote,
		SemiColon,
		QuestionMark,

		ENUM_LAST
	};

	enum class MouseButton {
		LeftButton,
		RightButton,
		MiddleButton,
		
		ENUM_LAST,
	};

	/**
	 * Registers a key input provider
	 */
	void register_key_provider(Unique<IKeyInputProvider> provider);

	/**
	 * Registers a mouse input provider
	 */
	void register_mouse_provider(Unique<IMouseInputProvider> provider);

	/**
	 * Registers a character input provider
	 */
	void register_character_provider(Unique<ICharacterInputProvider> provider);

	/**
	 * Checks if a key is currently being pressed
	 */
	bool is_pressed(Key key);

	/**
	 * Checks if a mouse button is being pressed
	 */
	bool is_pressed(MouseButton button);

	/**
	 * Checks if a key is being held
	 */
	bool is_held(Key key);

	/**
	 * Checks if a mouse button is being held
	 */
	bool is_held(MouseButton button);

	/**
	 * Checks if a key is being released
	 */
	bool is_released(Key key);

	/**
	 * Checks if a mouse button is being released
	 */
	bool is_released(MouseButton button);
}
