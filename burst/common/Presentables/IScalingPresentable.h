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
	 * Interface for listening for scaling persentable events
	 */
	class IScalingPresentableListener
	{
	public:
		virtual ~IScalingPresentableListener() = default;

		/**
		 * Invokes the on scale changed method
		 * 
		 * \param width: The new width
		 * \param height: The new height
		 */
		virtual void on_scale_changed(u32 width, u32 height) = 0;
	};

	/**
	 * A scaling presentable that signals when its rescaled.
	 */
	class IScalingPresentableSignaler : public IScalingPresentable
	{
	public:

		virtual ~IScalingPresentableSignaler() = default;

		/**
		 * Adds a scale listener.
		 */
		virtual Subscription add_scale_listener(IScalingPresentableListener *callback) = 0;
	};
}
