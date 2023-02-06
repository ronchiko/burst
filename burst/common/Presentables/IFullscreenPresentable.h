#pragma once

#include "../Types/IToken.h"
#include "IScalingPresentable.h"

namespace burst {
	/**
	 * The possible modes a fullscreen presentable can be in.
	 */
	enum class FullscreenMode{
		Windowed,
		Maximized,
		Fullscreen
	};

	/**
	 * A presentable that can be scaled according to the computers screen resulotion.
	 */
	class IFullscreenPresentable : public IScalingPresentable
	{
	public:
		IFACE_DESTRUCTOR(IFullscreenPresentable);

		/**
		 * Sets this presentable mode.
		 * 
		 * \param mode: The mode to set the presentable to
		 */
		IFACE_FUNC(void set_mode(FullscreenMode mode));
	};

	/**
	 * A IFullscreenPresentable that can signals when its mode is changed.
	 */
	class IFullscreenPresentableSignaler : public IFullscreenPresentable
	{
	public:
		using FullscreenCallback = void (*)(FullscreenMode mode);

		IFACE_DESTRUCTOR(IFullscreenPresentableSignaler);

		/**
		 * Adds a fullscreen listener.
		 */
		IFACE_FUNC(ITokenPtr add_fullscreen_listener(const FullscreenCallback& callback));
	};
}



