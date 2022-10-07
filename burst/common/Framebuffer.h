#pragma once

#include "Types.h"

namespace burst {
	class Framebuffer {
	public:
		virtual ~Framebuffer() = default;

		/**
		 * Gets the width of the framebuffer
		 */
		virtual u32 width() const = 0;

		/**
		 * Gets the height of the framebuffer
		 */
		virtual u32 height() const = 0;
	};
}