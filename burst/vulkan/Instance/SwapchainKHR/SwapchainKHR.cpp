#include "SwapchainKHR.h"

#include <burst/common/Log.h>

#include "../../Configuration.h"
#include "../../Errors.h"
#include "../Device/Device.h"
#include "../Gpu/Queues.h"
#include "../SurfaceKHR/GpuSurface.h"

#include "SwapchainImage.h"

/**
 * Finds and returns an item in a vector or returns a fallback value.
 *
 * \param vector: The vector to select from
 * \param fallback: The fallback value to select if no item was found
 * \param check: The check condition for the item
 * \param warning: The warning to show incase a fallback is chosen
 */
template<typename T>
T select(const burst::Vector<T>& vector,
		 const T& fallback,
		 std::function<bool(const T&)> check,
		 const burst::String& warning)
{
	auto result = std::find_if(vector.begin(), vector.end(), check);

	if(result == vector.end()) {
		// Didn't find target, write warning
		burst::log::warning(warning);
		return fallback;
	}

	return *result;
}

/**
 * Creates a swap extent from a IWindow.
 *
 * \param window: The window to use
 * \param capabilities: The limits of the extent
 */
static vk::Extent2D
swap_extent_from_window(burst::IWindow& window,
						const vk::SurfaceCapabilitiesKHR& capabilities)
{
	return vk::Extent2D{
		std::clamp(window.width(),
				   capabilities.minImageExtent.width,
				   capabilities.maxImageExtent.width),
		std::clamp(window.height(),
				   capabilities.minImageExtent.height,
				   capabilities.maxImageExtent.height),
	};
}

/**
 * Selects the image count from the capablities.
 *
 * \param capabilities: The surface capabilities
 * \return: The image count to use
 */
static burst::u32 select_image_count(const vk::SurfaceCapabilitiesKHR& capabilities)
{
	using namespace burst;

	u32 count = capabilities.minImageCount + 1;
	// Limit to maxImageCount
	if(count > capabilities.maxImageCount && capabilities.maxImageCount > 0) {
		count = capabilities.maxImageCount;
	}

	return count;
}

namespace burst::vulkan {

	u32 SwapchainKHR::width() const
	{
		return m_Cache.swap_extent.width;
	}

	u32 SwapchainKHR::height() const
	{
		return m_Cache.swap_extent.height;
	}

	vk::SurfaceFormatKHR SwapchainKHR::format() const
	{
		return m_Cache.format;
	}

	vk::raii::SwapchainKHR
	SwapchainKHR::_create_swapchain_khr(Device& device,
										const SurfaceKHR& surface,
										const Cache& cache,
										const Configuration& config)
	{
		vk::SwapchainCreateInfoKHR info(
			vk::SwapchainCreateFlagsKHR(0), // No flags
			static_cast<vk::SurfaceKHR>(surface),
			cache.image_count,
			cache.format.format,
			cache.format.colorSpace,
			cache.swap_extent,
			1, // Image array layers
			static_cast<vk::ImageUsageFlagBits>(config.swapchain.usage),
			vk::SharingMode::eExclusive,		 // sharing mode
			0,									 // number of queues
			cache.queues_family_indecies.data(), // queues array
			cache.capabilities.currentTransform,
			static_cast<vk::CompositeAlphaFlagBitsKHR>(config.swapchain.composite),
			cache.present_mode,
			true, // clipped
			vk::SwapchainKHR{},
			nullptr);

		// Prefer concurrent sharing if possible
		// TODO: More then two queues
		ASSERT(cache.queues_family_indecies.size() == 2,
			   "Queue size larger then 2 isn't implemented");
		if(cache.queues_family_indecies[0] != cache.queues_family_indecies[1]) {
			info.queueFamilyIndexCount = 2;
			info.imageSharingMode = vk::SharingMode::eConcurrent;
		}

		auto swapchain = static_cast<vk::Device>(device).createSwapchainKHR(info);


		return vk::raii::SwapchainKHR(static_cast<vk::raii::Device&>(device),
									  swapchain);
	}

	SwapchainKHR SwapchainKHR::create(Device& device,
									  GpuSurfaceBinding& surface,
									  IWindow& window,
									  Queues& queues,
									  const Configuration& config)
	{
		auto support = surface.get_surface_support_options();
		if(!support.is_ok()) {
			throw RuntimeError::make("Invalid support options for swapchain");
		}

		auto format = select<vk::SurfaceFormatKHR>(
			support.formats,
			support.formats[0],
			[](const vk::SurfaceFormatKHR& format) {
				return format.colorSpace == vk::ColorSpaceKHR::eSrgbNonlinear ||
					   format.format == vk::Format::eB8G8R8A8Srgb;
			},
			"Didn't find optimal surface format, using non-optimal one");
		auto present = select<vk::PresentModeKHR>(
			support.present_modes,
			vk::PresentModeKHR::eFifo,
			[](const vk::PresentModeKHR& mode) {
				return mode == vk::PresentModeKHR::eMailbox;
			},
			"Didn't find optimal present mode, using FIFO");

		auto swap_extent = support.capabilities.currentExtent;
		if(swap_extent.width == std::numeric_limits<u32>::max()) {
			swap_extent = swap_extent_from_window(window, support.capabilities);
		}

		Vector<u32> queues_indecies{
			queues[QueueType::Graphics].value(),
			queues[QueueType::Present].value(),
		};

		// Create the swapchain cache
		Cache cache{
			support.capabilities,
			format,
			present,
			swap_extent,
			select_image_count(support.capabilities), // Image count
			queues_indecies,
		};

		auto swapchain =
			_create_swapchain_khr(device, surface.surface(), cache, config);

		log::debug("Created new swapchain");
		return SwapchainKHR(device, std::move(swapchain), std::move(cache));
	}

	Vector<Unique<IImage>> SwapchainKHR::create_images() const
	{
		return convert<Vector<Unique<IImage>>>(
			m_Swapchain.getImages(), [this](const VkImage& image) {
				return Unique<IImage>(new SwapchainImage{
					image,
					m_Cache.format,
					{
						m_Cache.swap_extent.width,
						m_Cache.swap_extent.height,
					},
				});
			});
	}

	u32 SwapchainKHR::acquire_next_image(Semaphore& semaphore, u64 timeout)
	{
		auto result = device().acquireNextImageKHR(
			*m_Swapchain, timeout, static_cast<vk::Semaphore>(semaphore));

		if(result.result != vk::Result::eSuccess) {
			throw VulkanError("Failed to acquire next image", result.result);
		}

		return result.value;
	}

	Subscription SwapchainKHR::register_observer(ISwapchainObserver *observer)
	{
		return m_Observers.subscribe(observer);
	}

	void SwapchainKHR::notify_resize_happend()
	{
		m_Observers.notify(&ISwapchainObserver::on_swapchain_resized, *this);
	}

	SwapchainKHR::operator vk::SwapchainKHR() const
	{
		return *m_Swapchain;
	}

	SwapchainKHR::SwapchainKHR(Device& device,
							   vk::raii::SwapchainKHR swaphchain,
							   Cache cache)
		: mix::DeviceBound(device)
		, m_Swapchain(std::move(swaphchain))
		, m_Cache(cache)
	{}
}
