#pragma once

#include "../Types/IToken.h"
#include "IPresentable.h"

namespace burst {

	/**
	 * A presentable object that can be scaled.
	 */
	class IScalingPresentable : public IPresentable
	{
	public:
		IFACE_DESTRUCTOR(IScalingPresentable);
		
		/**
		 * Rescales this presentable.
		 * 
		 * \param width: The width of the presentable
		 * \param height: The height of the presentable
		 */
		IFACE_FUNC(void rescale(u32 width, u32 height));
	};

	/**
	 * A scaling presentable that signals when its rescaled.
	 */
	class IScalingPresentableSignaler : public IScalingPresentable
	{
	public:
		using ScaleCallback = void (*)(u32, u32);

		IFACE_DESTRUCTOR(IScalingPresentableSignaler);
		
		/**
		 * Adds a scale listener.
		 */
		IFACE_FUNC(ITokenPtr add_scale_listener(const ScaleCallback& callback));
	};
}


