#pragma once

#include "../Types.h"
#include "IPresentable.h"

namespace burst {

	/**
	 * A presentable object that run in realtime.
	 */
	class IRealtimePresentable : public IPresentable
	{
	public:
		IFACE_DESTRUCTOR(IRealtimePresentable);

		/**
		 * Checks if the presentable object is still active.
		 */
		IFACE_FUNC(bool is_active() const);
	};
}
