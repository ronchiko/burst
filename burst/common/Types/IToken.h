#pragma once

#include "../Types.h"

namespace burst {

	/**
	 * A generic object that repsentents an ownership token.
	 */
	class IOwnershipToken
	{
	public:
		virtual ~IOwnershipToken() = default;
	};

	/**
	 * Unique IOwnership token.
	 */
	using ITokenPtr = Unique<IOwnershipToken>;

	inline ITokenPtr make_token(IOwnershipToken* token) {
		return ITokenPtr(token);
	}
}


