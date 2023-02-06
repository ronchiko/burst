#include "KeyInputProvider.h"

#include <unordered_map>

#include <GLFW/glfw3.h>

#include <burst/common/Types.h>
#include <burst/common/Log.h>
#include <burst/common/Input/Input.h>

enum class KeyState {
	Free,
	Pressed,
	Held,
	Released
};

static KeyState g_Keys[static_cast<burst::u32>(burst::input::Key::ENUM_LAST)];

static const burst::HashMap<int, burst::input::Key> KEY_MAPPING({
	{ GLFW_KEY_A,				burst::input::Key::A },
	{ GLFW_KEY_B,				burst::input::Key::B },
	{ GLFW_KEY_C,				burst::input::Key::C },
	{ GLFW_KEY_D,				burst::input::Key::D },
	{ GLFW_KEY_E,				burst::input::Key::E },
	{ GLFW_KEY_F,				burst::input::Key::F },
	{ GLFW_KEY_G,				burst::input::Key::G },
	{ GLFW_KEY_H,				burst::input::Key::H },
	{ GLFW_KEY_I,				burst::input::Key::I },
	{ GLFW_KEY_J,				burst::input::Key::J },
	{ GLFW_KEY_K,				burst::input::Key::K },
	{ GLFW_KEY_L,				burst::input::Key::L },
	{ GLFW_KEY_M,				burst::input::Key::M },
	{ GLFW_KEY_N,				burst::input::Key::N },
	{ GLFW_KEY_O,				burst::input::Key::O },
	{ GLFW_KEY_P,				burst::input::Key::P },
	{ GLFW_KEY_Q,				burst::input::Key::Q },
	{ GLFW_KEY_R,				burst::input::Key::R },
	{ GLFW_KEY_S,				burst::input::Key::S },
	{ GLFW_KEY_T,				burst::input::Key::T },
	{ GLFW_KEY_U,				burst::input::Key::U },
	{ GLFW_KEY_V,				burst::input::Key::V },
	{ GLFW_KEY_W,				burst::input::Key::W },
	{ GLFW_KEY_X,				burst::input::Key::X },
	{ GLFW_KEY_Y,				burst::input::Key::Y },
	{ GLFW_KEY_Z,				burst::input::Key::Z },
	{ GLFW_KEY_LEFT,			burst::input::Key::Left },
	{ GLFW_KEY_RIGHT,			burst::input::Key::Right },
	{ GLFW_KEY_UP,				burst::input::Key::Up },
	{ GLFW_KEY_DOWN,			burst::input::Key::Down },
	{ GLFW_KEY_SPACE,			burst::input::Key::Space },
	{ GLFW_KEY_ESCAPE,			burst::input::Key::Escape },
	{ GLFW_KEY_ENTER,			burst::input::Key::Enter },
	{ GLFW_KEY_LEFT_SHIFT,		burst::input::Key::LeftShift },
	{ GLFW_KEY_RIGHT_SHIFT,		burst::input::Key::RightShift },
	{ GLFW_KEY_LEFT_CONTROL,	burst::input::Key::LeftCtrl },
	{ GLFW_KEY_RIGHT_CONTROL,	burst::input::Key::RightCtrl },
	{ GLFW_KEY_LEFT_ALT,		burst::input::Key::LeftAlt },
	{ GLFW_KEY_RIGHT_ALT,		burst::input::Key::RightAlt },
	{ GLFW_KEY_0,				burst::input::Key::Num0 },				
	{ GLFW_KEY_1,				burst::input::Key::Num1 },				
	{ GLFW_KEY_2,				burst::input::Key::Num2 },				
	{ GLFW_KEY_3,				burst::input::Key::Num3 },				
	{ GLFW_KEY_4,				burst::input::Key::Num4 },				
	{ GLFW_KEY_5,				burst::input::Key::Num5 },				
	{ GLFW_KEY_6,				burst::input::Key::Num6 },				
	{ GLFW_KEY_7,				burst::input::Key::Num7 },				
	{ GLFW_KEY_8,				burst::input::Key::Num8 },				
	{ GLFW_KEY_9,				burst::input::Key::Num9 },
});


void glfw_key_event_handler(GLFWwindow* window, int key, int scancode, int action, int mods) {
	try {
		if (action == GLFW_PRESS || action == GLFW_RELEASE) {
			auto burst_key = KEY_MAPPING.at(key);
			g_Keys[static_cast<burst::u32>(burst_key)] =
				action == GLFW_PRESS ? KeyState::Pressed : KeyState::Released;
		}
	} 
	catch (const std::out_of_range&) {
		burst::log::error("Unmapped key error, Key:", key, ", scancode: ", scancode);
	}
}

void glfw_advance_key_buffers() {
	for (auto& key : g_Keys) {
		if (key == KeyState::Pressed) key = KeyState::Held;
		if (key == KeyState::Released) key = KeyState::Free;
	}
}

bool burst::glfw::KeyInputProvider::is_held(burst::input::Key key) {
	return g_Keys[static_cast<burst::u32>(key)] == KeyState::Held;
}

bool burst::glfw::KeyInputProvider::is_pressed(burst::input::Key key) {
	return g_Keys[static_cast<burst::u32>(key)] == KeyState::Pressed;
}

bool burst::glfw::KeyInputProvider::is_released(burst::input::Key key) {
	return g_Keys[static_cast<burst::u32>(key)] == KeyState::Released;
}