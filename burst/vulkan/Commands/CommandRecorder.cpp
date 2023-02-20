#include "CommandRecorder.h"

#include <burst/common/Const.h>
#include <burst/common/Log.h>

#include "CommandBuffer.h"

namespace burst::vulkan {
	CommandRecorder::CommandRecorder(CommandBuffer& buffer)
		: m_Buffer(buffer)
	{
		CHECK(m_Buffer.start_recording(), "Failed to start recording");
	}

	CommandRecorder::~CommandRecorder()
	{
		m_Buffer.stop_recording();
	}
}
