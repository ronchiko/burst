#pragma once

#include <burst/Common/Input/Providers/IKeyInputProvider.h>

#include "../Events/IKeyEventListener.h"

namespace burst::glfw {
	class KeyInputProvider final : public input::IKeyInputProvider,
								   public burst::glfw::IKeyEventListener
	{
	public:
		explicit KeyInputProvider();

		virtual bool is_pressed(input::Key key) override;

		virtual bool is_held(input::Key key) override;

		virtual bool is_released(input::Key key) override;

		virtual void on_key_event(GLFWwindow *window, int key, int scancode, int action, int mods);

	private:
		Subscription m_GlfwKeyEventSubscription;
	};
}
