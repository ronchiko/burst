#pragma once

#include "Types.h"

namespace burst {
	INTERFACE Framebuffer{
	public:
		IFACE_DESTRUCTOR(Framebuffer);

		/**
		 * Gets the width of the framebuffer
		 */
		IFACE_FUNC(u32 width() const);

		/**
		 * Gets the height of the framebuffer
		 */
		IFACE_FUNC(u32 height() const);
	};
}