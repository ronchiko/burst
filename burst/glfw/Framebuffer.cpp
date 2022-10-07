#include "Framebuffer.h"

burst::glfw::Framebuffer::Framebuffer(GLFWwindow* window) 
	: burst::Framebuffer()
	, m_Window(window)
{}

burst::u32 burst::glfw::Framebuffer::width() const {
	burst::i32 width;
	glfwGetFramebufferSize(m_Window, &width, nullptr);

	return width;
}

burst::u32 burst::glfw::Framebuffer::height() const {
	burst::i32 height;
	glfwGetFramebufferSize(m_Window, nullptr, &height);

	return height;
}