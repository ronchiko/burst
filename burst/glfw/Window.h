#pragma once

#include <string>

#include <GLFW/glfw3.h>

#include <burst/Common/Types.h>
#include <burst/Common/Types/Notifier.h>
#include <burst/Common/Presentables/IFullscreenPresentable.h>

#include "Events/IResizeEventListener.h"

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
				   public burst::IFullscreenPresentableSignaler,
				   public burst::glfw::IResizeEventListener
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
		Subscription add_fullscreen_listener(IFullscreenPresentableListener *callback);

		Subscription add_scale_listener(IScalingPresentableListener *callback);
		
		/* -------- Event listener ------------------------------ */
		virtual void on_window_resized(GLFWwindow *window, int width, int height) override;

	private:
		void _window_owner_guard() const;

		struct Data;

		static Unique<Data> make_window_data(
			Uint2 scale, const String& title, const AdditionalWindowSettings& more);

		Unique<Data> m_Data;
		Notifier<IScalingPresentableListener> m_ScaleCallbacks;
		Notifier<IFullscreenPresentableListener> m_FullscreenCallbacks;

		Subscription m_GlfwResizeSubscription;
	};
}