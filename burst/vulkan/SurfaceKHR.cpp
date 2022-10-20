#include "SurfaceKHR.h"

#include <Windows.h>
#include <vulkan/vulkan_win32.h>

#include "Validation.h"

using namespace burst;

static vk::raii::SurfaceKHR create_surface_win32(
	const vk::raii::Instance& instance,
	Window& window
) {
	VkWin32SurfaceCreateInfoKHR create_info{};
	create_info.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
	create_info.hwnd = static_cast<HWND>(window.window_handle());
	create_info.hinstance = GetModuleHandleW(nullptr);

	VkSurfaceKHR surface = nullptr;
	VkResult result = vkCreateWin32SurfaceKHR(
		*instance,
		&create_info,
		vulkan::NO_ALLOCATOR,
		&surface);
	if (result != VK_SUCCESS) {
		throw RuntimeError::make("Failed to create SurfaceKHR, Error: ", result);
	}

	return vk::raii::SurfaceKHR(instance, surface);
}

namespace burst::vulkan {

	SurfaceKHR::SurfaceKHR() : m_Surface(nullptr) {}

	void SurfaceKHR::add_requirements(InstanceRequirements&) const {}

	void SurfaceKHR::init(
		const vk::raii::Instance& instance,
		const AdditionalCreateInfo& create_info
	) {
		if (nullptr == create_info.window) {
			throw StaticError("SurfaceKHR component requires a window");
		}

#ifdef _WIN32
		m_Surface = std::move(create_surface_win32(instance, *create_info.window));
#else
#error Surfaces are only supported for win32
#endif
	}

	const vk::raii::SurfaceKHR& SurfaceKHR::surface() const {
		return m_Surface;
	}
}
