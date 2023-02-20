#pragma once

#include "../Types.h"

namespace burst {
	/**
	 * An object that can be presented (such a window).
	 */
	class IPresentable
	{
	public:
		virtual ~IPresentable() = default;

		/**
		 * The width of the presentable object.
		 */
		virtual u32 width() const = 0;

		/**
		 * The height of the presentable object.
		 */
		virtual u32 height() const = 0;

		/**
		 * Updates this presentable object.
		 */
		virtual void update() = 0;
	};
}
