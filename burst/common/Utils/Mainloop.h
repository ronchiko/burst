#pragma once

#include "../IRenderer.h"
#include "../Presentables/IWindow.h"

namespace burst {
	/**
	 * A class the represents the mainloop logic of the engine.
	 */
	class Mainloop
	{
	public:
		Mainloop(Unique<IWindow> window, Unique<IRenderer>);

		void run();

	private:
		Unique<IWindow> m_Window;
		Unique<IRenderer> m_Renderer;
	};
}
