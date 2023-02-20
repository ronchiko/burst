#include "Window.h"

#include <burst/common/Error.h>
#include <burst/common/Log.h>
#include <burst/common/utils/Monitor.h>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

#include "Error.h"
#include "MonitorProvider.h"

#define OPERATION_GUARD _window_owner_guard()

extern void glfw_key_event_handler(GLFWwindow *, int, int, int, int);
extern void glfw_advance_key_buffers();

namespace burst::glfw {
	using AutoWindow = std::unique_ptr<std::remove_pointer_t<GLFWwindow>,
									   decltype(&glfwDestroyWindow)>;

	struct Window::Data
	{
		AutoWindow window;

		Uint2 scale;
		FullscreenMode fullscreen;
	};

	static AutoWindow
	create_window(u32 width, u32 height, const String& title, bool resizable)
	{
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

		auto window =
			glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
		if(nullptr == window) {
			throw burst::glfw::GlfwError("Failed to create window");
		}

		glfwSetKeyCallback(window, glfw_key_event_handler);

		return { window, glfwDestroyWindow };
	}

	Unique<Window::Data> Window::make_window_data(
		Uint2 scale, const String& title, const AdditionalWindowSettings& more)
	{
		auto data = std::make_unique<Window::Data>(
			create_window(scale.x, scale.y, title, more.scalable), scale, more.mode);

		return data;
	}

	Window::Window(const String& title,
				   u32 width,
				   u32 height,
				   const AdditionalWindowSettings& additional)
		: m_Data(make_window_data({ width, height }, title, additional))
		, m_ScaleCallbacks()
		, m_FullscreenCallbacks()
	{}

	u32 Window::width() const
	{
		OPERATION_GUARD;

		return m_Data->scale.x;
	}

	u32 Window::height() const
	{
		OPERATION_GUARD;

		return m_Data->scale.y;
	}

	bool Window::is_active() const
	{
		OPERATION_GUARD;

		glfwPollEvents();
		return !glfwWindowShouldClose(m_Data->window.get());
	}

	void Window::update()
	{
		OPERATION_GUARD;

		// glfwSwapBuffers(m_Window);
		glfw_advance_key_buffers();
	}

	Vector<vulkan::Requirement> burst::glfw::Window::get_requirements() const
	{
		using namespace vulkan;

		u32 count = 0;
		const char **extensions = glfwGetRequiredInstanceExtensions(&count);

		return convert<Vector<Requirement>>(
			Vector<const char *>{ extensions, extensions + count },
			[](const auto *ext) {
				return Requirement{ RequirementType::InstanceExtension, ext };
			});
	}

	Window::Identifier Window::identifier() const
	{
		OPERATION_GUARD;

		return glfwGetWin32Window(m_Data->window.get());
	}

	void Window::rescale(u32 w, u32 h)
	{
		OPERATION_GUARD;

		glfwSetWindowSize(m_Data->window.get(), w, h);
		m_ScaleCallbacks.notify(w, h);
	}

	void Window::set_mode(FullscreenMode mode)
	{
		OPERATION_GUARD;

		auto resolution = burst::monitor::resolution();

		burst::i32 x, y;
		glfwGetWindowPos(m_Data->window.get(), &x, &y);

		switch(mode) {
		case burst::FullscreenMode::Windowed:
			glfwSetWindowMonitor(m_Data->window.get(),
								 nullptr,
								 x,
								 y,
								 m_Data->scale.x,
								 m_Data->scale.y,
								 GLFW_DONT_CARE);
			break;
		case burst::FullscreenMode::Maximized:
			glfwSetWindowMonitor(m_Data->window.get(),
								 nullptr,
								 0,
								 0,
								 resolution.x,
								 resolution.y,
								 GLFW_DONT_CARE);
			break;
		case burst::FullscreenMode::Fullscreen:
			try {
				auto *glfw_provider =
					force_upcast<glfw::MonitorProvider>(monitor::get_provider());

				auto *monitor = glfw_provider->get_raw_primary_monitor();

				glfwSetWindowMonitor(m_Data->window.get(),
									 monitor,
									 0,
									 0,
									 resolution.x,
									 resolution.y,
									 GLFW_DONT_CARE);
			} catch(const std::exception& err) {
				// This might fail because of upcast, If we cant upcast we can't set
				// the monitor Then in release the next best thing is a maximized
				// window, so do it
				burst::log::error("Failed to set fullscreen, trying maximized: ",
								  err.what());
				FALLBACK(set_mode(FullscreenMode::Maximized));
			}
			break;

		default:
			throw GlfwError("Unsupported window mode");
			break;
		}
	}

	Subscription Window::add_fullscreen_listener(FullscreenCallback *callback)
	{
		return m_FullscreenCallbacks.subscribe(callback);
	}

	Subscription Window::add_scale_listener(ScaleCallback *callback)
	{
		return m_ScaleCallbacks.subscribe(callback);
	}

	void burst::glfw::Window::_window_owner_guard() const
	{
		if(nullptr == m_Data) {
			throw burst::NullptrError("No window :)");
		}
	}
}
