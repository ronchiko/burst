#pragma once

#include <burst/Common.h>

namespace burst::glfw {
	class KeyInputProvider final 
		: public input::IKeyInputProvider {
	
	public:
		virtual bool is_pressed(input::Key key) override;
		
		virtual bool is_held(input::Key key) override;
		
		virtual bool is_released(input::Key key) override;
	};
}
