#include "AbstractComponent.h"

void* burst::vulkan::AbstractComponent::component() {
	return m_AbstractType;
}

size_t burst::vulkan::AbstractComponent::hash() const {
	return m_Hash;
}

burst::vulkan::AbstractComponent::AbstractComponent(size_t hash, void *abstract) 
	: m_Hash(hash)
	, m_AbstractType(abstract)
{}
