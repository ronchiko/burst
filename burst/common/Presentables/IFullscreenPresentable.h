#pragma once

#include "../Types/Notifier.h"
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
		virtual ~IFullscreenPresentable() = default;

		/**
		 * Sets this presentable mode.
		 * 
		 * \param mode: The mode to set the presentable to
		 */
		virtual void set_mode(FullscreenMode mode) = 0;
	};

	/**
	 * A IFullscreenPresentable that can signals when its mode is changed.
	 */
	class IFullscreenPresentableSignaler : public IFullscreenPresentable
	{
	public:
		using FullscreenCallback = void(FullscreenMode mode);

		virtual ~IFullscreenPresentableSignaler() = default;

		/**
		 * Adds a fullscreen listener.
		 */
		virtual Subscription add_fullscreen_listener(FullscreenCallback *callback) = 0;
	};
}



