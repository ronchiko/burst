#include "Input.h"

#include "Error.h"

#include "Providers/ICharacterInputProvider.h"
#include "Providers/IKeyInputProvider.h"
#include "Providers/IMouseInputProvider.h"

namespace burst::input {

	static Unique<IKeyInputProvider> g_KeyInputProvider;
	static Unique<IMouseInputProvider> g_MouseInputProvider;
	static Unique<ICharacterInputProvider> g_CharacterInputProvider;

	/**
	 * Assets a provider is valid and can be accessed, throws exception on failure
	 */
	template<typename T>
	static auto validate(T *provider) -> T&
	{
		if(nullptr == provider) {
			throw burst::NullptrError("Missing input provider");
		}

		return *provider;
	}

	void register_key_provider(Unique<IKeyInputProvider> provider)
	{
		g_KeyInputProvider = std::move(provider);
	}

	void register_mouse_provider(Unique<IMouseInputProvider> provider)
	{
		g_MouseInputProvider = std::move(provider);
	}

	void register_character_provider(Unique<ICharacterInputProvider> provider)
	{
		g_CharacterInputProvider = std::move(provider);
	}

#pragma region Button / Key Handlers

	bool is_pressed(Key key)
	{
		return validate(g_KeyInputProvider.get()).is_pressed(key);
	}

	bool is_pressed(MouseButton button)
	{
		return validate(g_MouseInputProvider.get()).is_pressed(button);
	}

	bool is_held(Key key)
	{
		return validate(g_KeyInputProvider.get()).is_held(key);
	}

	bool is_held(MouseButton button)
	{
		return validate(g_MouseInputProvider.get()).is_held(button);
	}

	bool is_released(Key key)
	{
		return validate(g_KeyInputProvider.get()).is_released(key);
	}

	bool is_released(MouseButton button)
	{
		return validate(g_MouseInputProvider.get()).is_released(button);
	}

#pragma endregion
}
