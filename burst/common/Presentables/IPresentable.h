#pragma once

#include "../Types.h"

namespace burst {
	/**
	 * An object that can be presented (such a window).
	 */
	class IPresentable
	{
	public:
		IFACE_DESTRUCTOR(IPresentable);

		/**
		 * The width of the presentable object.
		 */
		IFACE_FUNC(u32 width() const);

		/**
		 * The height of the presentable object.
		 */
		IFACE_FUNC(u32 height() const);

		/**
		 * Updates this presentable object.
		 */
		IFACE_FUNC(void update());
	};
}
