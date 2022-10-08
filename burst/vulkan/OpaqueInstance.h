#pragma once

#include <vector>
#include <set>

#include <burst/Common.h>
#include <burst/Vulkan.h>

#include <vulkan/vulkan.h>
#include <vulkan/vulkan_raii.hpp>

#include "Component.h"
#include "QueueFamilyHandler.h"
#include "LogicalDevice.h"
#include "ComponentList.h"
#include "SurfaceKHR.h"

namespace burst::vulkan {
	constexpr const char* ENGINE_NAME = "Burst";
	constexpr burst::u32 ENGINE_VERSION = version(0, 1, 0);

	struct Extension {
		std::string name;
		u32 version;
	};

	/**
	* Gets the available vulkan extensions extensions
	*/
	std::vector<Extension> extensions();

	VkInstance make_instance(
		cstr name, 
		u32 version, 
		const std::vector<cstr>& requirements,
		const std::vector<cstr>& layers
	);

	struct InstanceDeleter {

		void operator()(VkInstance instance);
	};

	template<typename... Rest>
	class OpaqueInstance;

	template<>
	class OpaqueInstance<> {
	public:
		template<QueueFamily Q, Component... Comp>
		static OpaqueInstance<Comp...> make(cstr name, u32 version, Window* window) {
			ListComponentInfo<std::set<cstr>> list_info;
			if (nullptr != window) {
				auto window_requirements = window->get_requirements();
				list_info.extensions.insert(window_requirements.begin(), window_requirements.end());
			}

			OpaqueInstance<Comp...>::add_dependencies(list_info);

			ComponentCreateInfo create_info{
				.lists = list_info.convert<const std::vector<cstr>>(),
				.components = std::make_unique<ComponentList>(),
				.queue_family = std::make_unique<Q>(),
				.instance = nullptr,
				.window = window,
				.physical_device = nullptr,
				.device = nullptr,
			};

			VkInstance _instance = make_instance(
				name,
				version,
				create_info.lists.extensions,
				create_info.lists.validation_layers
			);
			create_info.instance = vk::raii::Instance(vk::raii::Context(), _instance);

			auto instance = OpaqueInstance<Comp...>(create_info);
			instance.late_initialize<Q, Comp...>(create_info, instance);
			return instance;
		}

		inline VkInstance instance() const {
			return *m_Instance;
		}

		inline const LogicalDevice& device() const {
			return m_LogicalDevice;
		}

		inline const PhysicalDevice& physical() const {
			return m_PhysicalDevice;
		}

		template<QueueFamily Q>
		Q& queue_family() const {
			return *reinterpret_cast<Q*>(m_QueueFamily.get());
		}

	protected:
		OpaqueInstance(ComponentCreateInfo& info)
			: m_Instance(nullptr)
			, m_PhysicalDevice(nullptr)
			, m_LogicalDevice(nullptr)
			, m_QueueFamily(nullptr) {}

		static void add_dependencies(ListComponentInfo<std::set<cstr>>&) {}

		void late_init(ComponentCreateInfo&) {}

	private:

		template<QueueFamily Q, Component... Comp>
		void late_initialize(
			ComponentCreateInfo& create_info,
			OpaqueInstance<Comp...>& instance) {
			
			std::optional<VkSurfaceKHR> surface = {};
			try {
				surface = create_info.components->get<SurfaceKHR>();
			} catch (const InstanceComponentNotFound&) {}
			
			create_info.physical_device = PhysicalDevice::select_suitable<Q>(
				create_info.instance,
				create_info.lists.device_extensions,
				surface
				);
			m_PhysicalDevice = PhysicalDevice(create_info.physical_device.value());

			m_PhysicalDevice.find_queue_indecies(
				*create_info.queue_family, 
				surface
			);
			instance.late_init(create_info);

			create_info.device = create_logical_device(m_PhysicalDevice.device(), create_info);
			instance.late_init(create_info);

			m_QueueFamily = std::move(create_info.queue_family);
						
			m_LogicalDevice = create_info.device;
			m_Instance = std::move(create_info.instance);
		}
		
		vk::raii::Instance m_Instance;
		PhysicalDevice m_PhysicalDevice = vk::raii::PhysicalDevice(nullptr);
		LogicalDevice m_LogicalDevice = nullptr;
		std::unique_ptr<QueueFamilyHandler> m_QueueFamily = nullptr;
	};

	class InstanceFactory {
	public:
		template<QueueFamily Q, Component... Comp>
		static OpaqueInstance<Comp...> make(cstr name, u32 version, Window* window) {
			return OpaqueInstance<>::make<Q, Comp...>(name, version, window);
		}
	};

	template<Component T>
	struct OpaqueInstanceComponent {
	public:
		OpaqueInstanceComponent(ComponentCreateInfo& info)
			: m_Component(create_component(info))
		{
			if (nullptr != m_Component) {
				info.components->push_back<T>(m_Component.get());
			}
		}

		void late_init(ComponentCreateInfo& info) 
		{
			if (m_Component != nullptr) {
				return;
			}

			m_Component = std::move(create_component(info));
			if (nullptr != m_Component) {
				info.components->push_back<T>(m_Component.get());
			}
		}

		bool is_initialized() const {
			return m_Component != nullptr;
		}

	private:
		static T::Type create_component(ComponentCreateInfo& info) {
			try {
				auto component =  std::move(T::create_component(info));
				return component;
			}
			catch (const WaitingForLaterInitialization&) {
				burst::log::debug(typeid(T).name(), " is waiting for later initialization");
				return nullptr;
			}
		}

		T::Type m_Component;
	};


	template<Component This, Component... Rest>
	class OpaqueInstance<This, Rest...> : 
		// Oddly this order of constructors caused the intended revesed effect
		// Should figure out if its an implementation thing, or what is going on
		private OpaqueInstanceComponent<This>,
		private OpaqueInstance<Rest...>
	{
	public:		
		template<QueueFamily Q>
		static OpaqueInstance<This, Rest...> make(cstr name, u32 version, Window* window) {
			return InstanceFactory::make<Q, This, Rest...>(name, version, window);
		}

	private:
		friend class OpaqueInstance<>;

		using Base = OpaqueInstance<Rest...>;
		using Container = OpaqueInstanceComponent<This>;

	protected:
		OpaqueInstance(ComponentCreateInfo& info) :
			Container(info), Base(info)
		{}

		static void add_dependencies(
			ListComponentInfo<std::set<cstr>>& lists
		) {
			This::add_dependencies(lists);
			Base::add_dependencies(lists);
		}

		void late_init(ComponentCreateInfo& info) {
			Container::late_init(info);
			Base::late_init(info);
		}
	};

}
