#include "Input.h"

#include "Error.h"

#include "KeyInputProvider.h"
#include "MouseInputProvider.h"
#include "CharacterInputProvider.h"

static std::unique_ptr<burst::input::KeyInputProvider>			g_KeyInputProvider;
static std::unique_ptr<burst::input::MouseInputProvider>		g_MouseInputProvider;
static std::unique_ptr<burst::input::CharacterInputProvider>	g_CharacterInputProvider;

/**
 * Assets a provider is valid and can be accessed, throws exception on failure
 */
template<typename T>
static auto validate(T* provider) -> T& {
	if (nullptr == provider) {
		throw burst::NullptrError("Missing input provider");
	}

	return *provider;
}

void burst::input::register_key_provider(
	std::unique_ptr<burst::input::KeyInputProvider> provider
) {
	g_KeyInputProvider = std::move(provider);
}

void burst::input::register_mouse_provider(
	std::unique_ptr<burst::input::MouseInputProvider> provider
) {
	g_MouseInputProvider = std::move(provider);
}

void burst::input::register_character_provider(
	std::unique_ptr<burst::input::CharacterInputProvider> provider
) {
	g_CharacterInputProvider = std::move(provider);
}

#pragma region Button/Key Handlers

bool burst::input::is_pressed(Key key) {
	return validate(g_KeyInputProvider.get()).is_pressed(key);
}

bool burst::input::is_pressed(MouseButton button) {
	return validate(g_MouseInputProvider.get()).is_pressed(button);
}

bool burst::input::is_held(Key key) {
	return validate(g_KeyInputProvider.get()).is_held(key);
}

bool burst::input::is_held(MouseButton button) {
	return validate(g_MouseInputProvider.get()).is_held(button);
}

bool burst::input::is_released(Key key) {
	return validate(g_KeyInputProvider.get()).is_released(key);
}

bool burst::input::is_released(MouseButton button) {
	return validate(g_MouseInputProvider.get()).is_released(button);
}

#pragma endregion