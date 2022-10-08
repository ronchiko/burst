#include "SurfaceKHR.h"

#include <Windows.h>
#include <vulkan/vulkan_win32.h>

#include "Validation.h"

using namespace burst;

void burst::vulkan::SurfaceKHRDeleter::operator()(VkSurfaceKHR surface) {
	if (surface != nullptr) {
		vkDestroySurfaceKHR(instance, surface, vulkan::NO_ALLOCATOR);
	}
}

static vulkan::AutoSurfaceKHR create_surface_win32(
	vk::Instance instance,
	Window& window
) {
	VkWin32SurfaceCreateInfoKHR create_info{};
	create_info.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
	create_info.hwnd = static_cast<HWND>(window.window_handle());
	create_info.hinstance = GetModuleHandleW(nullptr);

	VkSurfaceKHR surface = nullptr;
	VkResult result = vkCreateWin32SurfaceKHR(
		instance,
		&create_info,
		vulkan::NO_ALLOCATOR,
		&surface);
	if (result != VK_SUCCESS) {
		throw RuntimeError::make("Failed to create SurfaceKHR, Error: ", result);
	}

	return vulkan::AutoSurfaceKHR(surface, vulkan::SurfaceKHRDeleter(instance));
}

void burst::vulkan::SurfaceKHR::add_dependencies(ListComponentInfo<std::set<cstr>>&)
{}

burst::vulkan::SurfaceKHR::Type burst::vulkan::SurfaceKHR::create_component(
	const ComponentCreateInfo& create_info
) {
	if (nullptr == create_info.window) {
		throw StaticError("SurfaceKHR component requires a window");
	}
#ifdef _WIN32
	return create_surface_win32(*create_info.instance, *create_info.window);
#else
#error Surfaces are only supported for win32
#endif

}
