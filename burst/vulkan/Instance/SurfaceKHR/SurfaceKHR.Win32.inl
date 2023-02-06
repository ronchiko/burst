#pragma once

#include <Windows.h>
#include <vulkan/vulkan_win32.h>

#include "../../Utils/Burst.Windows.h"

#include <burst/common/Presentables/IWindow.h>


#include "../Instance.h"

namespace win32 {

	constexpr burst::u32 MESSAGE_MAX_SIZE = 512;

	static burst::String last_windows_error()
	{
		auto err = GetLastError();
		char message[MESSAGE_MAX_SIZE] = { 0 };

		FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM,
					   nullptr,
					   err,
					   LANG_USER_DEFAULT,
					   message,
					   MESSAGE_MAX_SIZE - 1,
					   nullptr);

		return burst::String(
			burst::concat("Windows Error: ", message, "(", err, ")"));
	}
}

vk::raii::SurfaceKHR create_surface(burst::vulkan::Instance& instance,
									const burst::IWindow& window)
{
	VkWin32SurfaceCreateInfoKHR info{};
	info.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
	info.hwnd = static_cast<HWND>(window.identifier());
	info.hinstance = GetModuleHandle(nullptr);

	VkSurfaceKHR surface = nullptr;
	auto result = vkCreateWin32SurfaceKHR(
		static_cast<vk::Instance>(instance), &info, nullptr, &surface);

	if(VK_SUCCESS != result) {
		throw burst::RuntimeError(win32::last_windows_error());
	}

	return vk::raii::SurfaceKHR(static_cast<vk::raii::Instance&>(instance), surface);
}
