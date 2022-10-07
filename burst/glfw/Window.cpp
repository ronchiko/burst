#include "Window.h"

#include "burst/common/Error.h"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

extern void glfw_key_event_handler(GLFWwindow*, int, int, int, int);
extern void glfw_advance_key_buffers();

static GLFWwindow* allocate_window(
	const std::string& title,
	burst::i32 width,
	burst::i32 height
) {
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	auto* window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

	glfwSetKeyCallback(window, glfw_key_event_handler);
	return window;
}

burst::glfw::Window::Window(
	std::string title,
	burst::i32 width,
	burst::i32 height
) 
	: m_Window(allocate_window(title, width, height))
	, m_FullscreenMode(WindowMode::WINDOWED)
	, m_IsScalable(true)
	, m_Title(std::move(title))
	, m_Framebuffer(m_Window)
{}

burst::glfw::Window::Window(burst::glfw::Window&& other) noexcept
	: m_Window(other.m_Window)
	, m_FullscreenMode(other.m_FullscreenMode)
	, m_IsScalable(other.m_IsScalable)
	, m_Title(std::move(other.m_Title))
	, m_Framebuffer(std::move(other.m_Framebuffer))
{
	other.m_Window = nullptr;
	other.m_Title = "";
}

burst::glfw::Window& burst::glfw::Window::operator=(burst::glfw::Window&& other) noexcept
{
	m_Window = other.m_Window;
	m_FullscreenMode = other.m_FullscreenMode;
	m_IsScalable = other.m_IsScalable;
	m_Title = std::move(other.m_Title);

	other.m_Window = nullptr;
	other.m_Title = "";

	return *this;
}

burst::glfw::Window::~Window() {
	if (nullptr != m_Window) {
		glfwDestroyWindow(m_Window);
	}
}

bool burst::glfw::Window::should_quit() {
	_window_owner_guard();

	glfwPollEvents();
	return glfwWindowShouldClose(m_Window);
}

void burst::glfw::Window::render() {
	_window_owner_guard();

	// glfwSwapBuffers(m_Window);
	glfw_advance_key_buffers();
}

burst::WindowInfo burst::glfw::Window::info() const {
	_window_owner_guard();
		
	burst::WindowInfo info;
	glfwGetWindowSize(m_Window, &info.width, &info.height);
	info.title = m_Title;
	info.fullscreen = m_FullscreenMode;

	return info;
}

void burst::glfw::Window::info(const burst::WindowInfo& info) {
	_window_owner_guard();

	burst::i32 x, y;
	glfwGetWindowPos(m_Window, &x, &y);
	glfwSetWindowSize(m_Window, info.width, info.height);
	m_Title = info.title;
	m_FullscreenMode = info.fullscreen;

	glfwSetWindowTitle(m_Window, info.title.c_str());

	auto* monitor = glfwGetPrimaryMonitor();
	switch (info.fullscreen)
	{
	case WindowMode::WINDOWED:
		glfwSetWindowMonitor(m_Window, nullptr, x, y, info.width, info.height, 0);
		break;

	case WindowMode::FULLSCREEN:
		glfwSetWindowMonitor(m_Window, monitor, 0, 0, info.width, info.height, 0);
		break;

	default:
		throw burst::StaticError("Fullscreen info is not supported");
	}
}

void burst::glfw::Window::_window_owner_guard() const {
	if (nullptr == m_Window) {
		throw burst::NullptrError("Window was not owned by anyone");
	}
}

std::vector<burst::cstr> burst::glfw::Window::get_requirements() const {
	u32 count = 0;
	const char** extensions = glfwGetRequiredInstanceExtensions(&count);

	return std::vector<burst::cstr>(extensions, extensions + count);
}

void* burst::glfw::Window::window_handle() const {
	_window_owner_guard();
	
	return glfwGetWin32Window(m_Window);
}

burst::Framebuffer& burst::glfw::Window::framebuffer() {
	return m_Framebuffer;
}