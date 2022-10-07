#pragma once

#include <GLFW/glfw3.h>

#include <burst/Common/Framebuffer.h>

namespace burst::glfw {
	class Framebuffer : public burst::Framebuffer {
	public:
		Framebuffer(GLFWwindow* window);

		virtual u32 width() const override;

		virtual u32 height() const override;
	
	private:
		GLFWwindow* m_Window;
	};
}