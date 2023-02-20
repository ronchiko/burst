#pragma once

#include <string>

#include <GLFW/glfw3.h>

#include <burst/Common/Types.h>
#include <burst/Common/Types/Notifier.h>
#include <burst/Common/Presentables/IFullscreenPresentable.h>

#include "burst/vulkan/IVulkanWindow.h"

namespace burst::glfw {

	struct AdditionalWindowSettings
	{
		bool scalable;
		FullscreenMode mode;
	};

	/**
	 * The generic GLFW window implementation.
	 */
	class Window : public burst::vulkan::IVulkanWindow,
				   public burst::IScalingPresentableSignaler,
				   public burst::IFullscreenPresentableSignaler
	{
	public:
		static constexpr AdditionalWindowSettings DEFAULT_SETTINGS = {
			true,
			FullscreenMode::Windowed,
		};

		explicit Window(const String& title,
			u32 width,
			u32 height,
			const AdditionalWindowSettings& = DEFAULT_SETTINGS);

		/*	-------- IPresentable ------------------------------ */
		virtual u32 width() const override;

		virtual u32 height() const override;

		virtual void update() override;

		/* --------- IRealtimePresntable ----------------------- */

		virtual bool is_active() const override;

		/* --------- IWindow ----------------------------------- */
		virtual Identifier identifier() const override;

		/* --------- IVulkanWindow ----------------------------- */
		virtual Vector<vulkan::Requirement> get_requirements() const override;

		/* --------- Scaling ----------------------------------- */
		void rescale(u32 width, u32 height);

		void set_mode(FullscreenMode mode);

		/* --------- Signaling ---------------------------------- */
		Subscription add_fullscreen_listener(FullscreenCallback *callback);

		Subscription add_scale_listener(ScaleCallback *callback);

	private:
		void _window_owner_guard() const;

		struct Data;

		static Unique<Data> make_window_data(
			Uint2 scale, const String& title, const AdditionalWindowSettings& more);

		Unique<Data> m_Data;
		Notifier<ScaleCallback> m_ScaleCallbacks;
		Notifier<FullscreenCallback> m_FullscreenCallbacks;
	};
}