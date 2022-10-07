#include "ComponentList.h"

#include "Errors.h"

burst::vulkan::ComponentList::ComponentList()
	: m_Components{}
{}

burst::vulkan::AbstractComponent& burst::vulkan::ComponentList::get(size_t hash) {
	auto iter = std::find_if(
		m_Components.begin(),
		m_Components.end(),
		[hash](const AbstractComponent& component) {
			return component.hash() == hash;
		});

	if (iter == m_Components.end()) {
		throw InstanceComponentNotFound(hash);
	}

	return *iter;
}
