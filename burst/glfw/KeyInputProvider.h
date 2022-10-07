#pragma once

#include "burst/common/KeyInputProvider.h"

namespace burst::glfw {
	class KeyInputProvider final 
		: public burst::input::KeyInputProvider {
	
	public:
		virtual bool is_pressed(burst::input::Key key) override;
		
		virtual bool is_held(burst::input::Key key) override;
		
		virtual bool is_released(burst::input::Key key) override;
	};
}
