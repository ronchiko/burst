#pragma once

#include "../Types/Notifier.h"

#include "IPresentable.h"

namespace burst {

	/**
	 * A presentable object that can be scaled.
	 */
	class IScalingPresentable : public IPresentable
	{
	public:
		virtual ~IScalingPresentable() = default;

		/**
		 * Rescales this presentable.
		 *
		 * \param width: The width of the presentable
		 * \param height: The height of the presentable
		 */
		virtual void rescale(u32 width, u32 height) = 0;
	};

	/**
	 * A scaling presentable that signals when its rescaled.
	 */
	class IScalingPresentableSignaler : public IScalingPresentable
	{
	public:
		using ScaleCallback = void(u32, u32);

		virtual ~IScalingPresentableSignaler() = default;

		/**
		 * Adds a scale listener.
		 */
		virtual Subscription add_scale_listener(ScaleCallback *callback) = 0;
	};
}
