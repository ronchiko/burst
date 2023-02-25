#include "SwapchainKHR.h"

#include <burst/common/Log.h>
#include <burst/common/Presentables/IScalingPresentable.h>

#include "burst/vulkan/Vk.h"

#include "../../Configuration.h"
#include "../../Errors.h"
#include "../Device/Device.h"
#include "../Gpu/Queues.h"
#include "../SurfaceKHR/GpuSurface.h"

#include "SwapchainCreator.h"
#include "SwapchainImage.h"

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

	Unique<SwapchainKHR> SwapchainKHR::create(Device& device,
											  GpuSurfaceBinding& surface,
											  IPresentable& window,
											  Queues& queues,
											  Shared<Configuration> config)
	{
		auto creator = std::make_unique<SwapchainCreator>(surface, window, queues, config);
		auto [swapchain, cache] = creator->create(device);

		log::debug("Created new swapchain");
		return Unique<SwapchainKHR>(new SwapchainKHR(device,
													 std::move(creator),
													 std::move(swapchain),
													 std::move(cache),
													 window));
	}

	Vector<Unique<IImage>> SwapchainKHR::create_images() const
	{
		return convert<Vector<Unique<IImage>>>(m_Swapchain.getImages(),
											   [this](const VkImage& image) {
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
		m_WasRescaled = false;
		u32 image_index = 0;

		const auto result = VK_CALL(vkAcquireNextImageKHR(static_cast<vk::Device>(m_Device),
														  *m_Swapchain,
														  timeout,
														  static_cast<vk::Semaphore>(semaphore),
														  VK_NULL_HANDLE,
														  &image_index));

		if(vk::Result::eErrorOutOfDateKHR == result) {
			force_recreation();
		} else if(result != vk::Result::eSuccess && result != vk::Result::eSuboptimalKHR) {
			throw VulkanError("Failed to acquire next image", result);
		}

		return image_index;
	}

	Subscription SwapchainKHR::register_observer(ISwapchainObserver *observer)
	{
		return m_Observers.subscribe(observer);
	}

	void SwapchainKHR::force_recreation()
	{
		// Only rescale once per frame
		if(m_WasRescaled) {
			return;
		}
		m_WasRescaled = true;

		const auto result = VK_CALL(vkDeviceWaitIdle(static_cast<vk::Device>(m_Device)));

		if(vk::Result::eSuccess != result) {
			burst::log::error("Failed to recreate SwapchainKHR: ", result);
			return;
		}

		m_Swapchain = nullptr;		// Free swapchain to reserve memory

		log::debug("Recreating swapchain");

		auto [swapchain, cache] = m_Creator->create(m_Device);
		m_Swapchain = std::move(swapchain);
		m_Cache = std::move(cache);

		m_Observers.notify(&ISwapchainObserver::on_swapchain_resized, *this);
	}

	void SwapchainKHR::on_scale_changed([[maybe_unused]] u32 width, [[maybe_unused]] u32 height)
	{
		force_recreation();
	}

	void SwapchainKHR::on_fullscreen_mode_changed([[maybe_unused]] FullscreenMode mode)
	{
		force_recreation();
	}

	SwapchainKHR::operator vk::SwapchainKHR() const
	{
		return *m_Swapchain;
	}

	SwapchainKHR::SwapchainKHR(Device& device,
							   Unique<SwapchainCreator> creator,
							   vk::raii::SwapchainKHR swaphchain,
							   SwapchainCache cache,
							   IPresentable& presentable)
		: mix::DeviceBound(device)
		, m_Creator(std::move(creator))
		, m_Swapchain(std::move(swaphchain))
		, m_Cache(cache)
		, m_Observers()
		, m_ResizeSubscriptions()
		, m_WasRescaled(false)
	{
		if(TRY_UPCAST(scalable, IScalingPresentableSignaler, &presentable)) {
			m_ResizeSubscriptions.push_back(scalable->add_scale_listener(this));
		}

		if(TRY_UPCAST(fullscreen, IFullscreenPresentableSignaler, &presentable)) {
			m_ResizeSubscriptions.push_back(fullscreen->add_fullscreen_listener(this));
		}
	}
}
