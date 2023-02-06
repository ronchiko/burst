#pragma once

#include "Types.h"
#include "Presentables/IPresentable.h"

namespace burst {

	/**
	 * Interface for a renderer.
	 */
	class IRenderer
	{
	public:
		IFACE_DESTRUCTOR(IRenderer);

		IFACE_FUNC(void render());
	};

}
