#include "Mainloop.h"

#include "Log.h"

namespace burst {
	Mainloop::Mainloop(
		Unique<IWindow> window, Unique<IRenderer> renderer)
		: m_Window(std::move(window))
		, m_Renderer(std::move(renderer))
	{}

	void Mainloop::run()
	{
		if (nullptr == m_Window || nullptr == m_Renderer) {
			burst::log::error("No window or renderer given to mainloop");
			return;
		}

		while(!m_Window->is_active()) {
			m_Renderer->render();

			m_Window->update();
		}
	}

}
