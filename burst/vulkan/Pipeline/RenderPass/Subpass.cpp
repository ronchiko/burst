#include "Subpass.h"

using namespace vk;

namespace burst::vulkan {
	Subpass::Subpass(Type type,
					 Vector<AttachmentReference> inputs,
					 Vector<AttachmentReference> outputs)
		: m_Type(type)
		, m_Inputs(std::move(inputs))
		, m_Outputs(std::move(outputs))
		, m_Description(SubpassDescription{
			  SubpassDescriptionFlags(),
			  static_cast<PipelineBindPoint>(type),
			  m_Inputs,
			  m_Outputs,
		  })
	{}

	Subpass::operator vk::SubpassDescription() const {
		return m_Description;
	}

}
