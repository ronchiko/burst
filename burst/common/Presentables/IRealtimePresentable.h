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
		virtual ~IRealtimePresentable() = default;

		/**
		 * Checks if the presentable object is still active.
		 */
		virtual bool is_active() const = 0;
	};
}
