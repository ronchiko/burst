#pragma once

#include <Burst/Common/Types.h>
#include <Burst/Common/Types/Behavior/Enum.h>
#include <Burst/Common/Types/Behavior/EnumAccess.h>

namespace burst::vulkan {

	enum class QueueType
	{
		Graphics = 0,
		Present
	};

	inline constexpr u32 LAST_QUEUE_INDEX = static_cast<u32>(QueueType::Present) + 1;

	/**
	 * The queues discovered by a GPU.
	 */
	class Queues : public MutableEnumAccess<QueueType, Array<Optional<u32>, 32>>
	{
	private:
		using Base = MutableEnumAccess<QueueType, Array<Optional<u32>, 32>>;

	public:
		Queues()
			: Base({})
		{}

		/**
		 * Checks this object has a queue of u32.
		 *
		 * \param queue: The queue to use
		 */
		bool has_queue(Enum<QueueType> queue) const
		{
			return at(static_cast<u32>(queue)).has_value();
		}

		/**
		 * Checks if this object all the queues specified.
		 */
		template<typename Q, typename... Qs>
		constexpr bool has_queues(Q queue, Qs... queues) const
		{
			if constexpr(sizeof...(queues) > 0) {
				return has_queue(queue) && has_queues(queues...);
			} else {
				return has_queue(queue);
			}
		}
	};
}
