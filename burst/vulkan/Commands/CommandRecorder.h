#pragma once

namespace burst::vulkan {
	class CommandBuffer;

	/**
	 * RAII Class for recording action on a command buffer.
	 */
	class CommandRecorder
	{
	public:
		explicit CommandRecorder(CommandBuffer& buffer);

		CommandRecorder(const CommandRecorder&) = delete;
		CommandRecorder(CommandRecorder&&) = delete;
		CommandRecorder& operator=(const CommandRecorder&) = delete;
		CommandRecorder& operator=(CommandRecorder&&) = delete;

		~CommandRecorder();

	private:
		CommandBuffer& m_Buffer;
	};
}
