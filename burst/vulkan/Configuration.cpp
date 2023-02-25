#include "Configuration.h"

#include "Instance/Gpu/Analyzers/BasicGpuAnalyzer.h"
#include "Instance/Gpu/Locators/GraphicsQueueLocator.h"

#include "Pipeline/Shaders/Embedded.h"
#include "Pipeline/Shaders/Loaders/BuiltinShader.h"

#include "Pipeline/Dynamic States/DynamicViewportHandler.h"


constexpr burst::cstr DEBUG_VALIDATION_LAYER = "VK_LAYER_KHRONOS_validation";

namespace burst::vulkan {
	static Unique<GraphicsQueueLocator> g_DefaultQueueLocator =
		std::make_unique<GraphicsQueueLocator>();

	static Unique<IGpuAnalyzer> g_DefaultGpuAnalzyer =
		std::make_unique<analyzers::BasicGpuAnalyzer>();

	static Unique<IDynamicStateHandler> g_DynamicViewportHandler =
		std::make_unique<DynamicViewportHandler>();

	Shared<Configuration> Configuration::create_default_configuration()
	{
		using enum RequirementType;

		return Shared<Configuration>(new Configuration{
			{
				Requirement{ InstanceExtension, VK_KHR_SURFACE_EXTENSION_NAME },
				Requirement{ DeviceExtension, VK_KHR_SWAPCHAIN_EXTENSION_NAME },
#ifdef _DEBUG
				Requirement{ InstanceExtension, VK_EXT_DEBUG_UTILS_EXTENSION_NAME },
				Requirement{ ValidationLayer, DEBUG_VALIDATION_LAYER },
#endif
			}, // Requirements
			Configuration::Instance{
				true, // Create surface
			},
			Configuration::Gpu{
				{
					g_DefaultQueueLocator.get(),
				},							// Locators
				g_DefaultGpuAnalzyer.get(), // Analyzer
			},
			Configuration::Swapchain{
				ImageUsage::AttachColor, // Image usage
				CompositeAlpha::Opaque,	 // Composite alpha
			},
			Configuration::Pipeline{
				{}, // Rasterizer
				{}, // multisample
				Vector<IShaderLoader *>{
					// Shaders
					g_DefaultVertexShader.get(),
					g_DefaultFragmentShader.get(),
				},
				Vector<IDynamicStateHandler *>{
					// Dynamic states
					g_DynamicViewportHandler.get(),
				},
				vk::PrimitiveTopology::eTriangleList,
				Vector<Configuration::Pipeline::ColorAttachment>{
					Configuration::Pipeline::ColorAttachment(),
				},
			}
		});
	}
}