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
		virtual ~IRenderer() = default;

		virtual void render() = 0;
	};

}
