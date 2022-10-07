#pragma once

#include <string>

#include <GLFW/glfw3.h>

#include "burst/common/Types.h"
#include "burst/common/Window.h"

#include "Framebuffer.h"

namespace burst::glfw {
	class Window : public burst::Window {
	public:
		Window(
			std::string title,
			burst::i32 width,
			burst::i32 height
		);

		Window(const Window&) = delete;
		Window& operator=(const Window&) = delete;

		Window(Window&&) noexcept;
		Window& operator=(Window&&) noexcept;

		virtual ~Window() override;

		virtual bool should_quit() override;

		virtual void render() override;

		virtual burst::WindowInfo info() const override;

		virtual void info(const burst::WindowInfo&) override;

		virtual std::vector<cstr> get_requirements() const override;

		virtual void* window_handle() const override;

		virtual burst::Framebuffer& framebuffer() override;

	private:
		void _window_owner_guard() const;

		GLFWwindow *m_Window;
		WindowMode m_FullscreenMode = WindowMode::WINDOWED;
		bool m_IsScalable = false;
		std::string m_Title;
		burst::glfw::Framebuffer m_Framebuffer;
	};
}