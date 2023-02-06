#pragma once

#include "../Concepts.h"
#include "../Types.h"

#include "IToken.h"

namespace burst {
	/**
	 * A list to store callbacks.
	 */
	template<typename CallbackType>
	requires std::equality_comparable<CallbackType>
	class SignalList
	{
	public:
		/**
		 * A RAII manager for the list.
		 */
		class Token : public IOwnershipToken
		{
		public:
			Token(SignalList& list, const CallbackType& item)
				: m_List(list)
				, m_Item(&item)
			{}

			Token(const Token&) = delete;
			Token& operator=(const Token&) = delete;

			Token(Token&& other) 
				: m_List(other.m_List)
				, m_Item(other.m_Item)
			{
				other.m_Item = nullptr;
			}

			Token& operator=(Token&& other) {
				_release();

				m_Item = other.m_Item;
				m_List = other.m_List;
				other.m_Item = nullptr;

				return *this;
			}

			~Token()
			{
				_release();
			}

		private:
			void _release() {
				if(nullptr != m_Item) {
					m_List.remove(*m_Item);
				}
			}

			SignalList& m_List;
			const CallbackType * m_Item;
		};

		explicit SignalList()
			: m_Callbacks()
		{}

		SignalList(nullptr_t) 
			: m_Callbacks()
		{}

		SignalList& operator=(nullptr_t) {
			m_Callbacks.clear();

			return *this;
		}

		/**
		 * Adds a callback to the list.
		 *
		 * \param callback: The callback to add
		 * \returns: A pointer to a token when this operation was successful, 
		 *			 when the token is destroyed, the callback will no longer
		 *			 be called
		 */
		ITokenPtr add(const CallbackType& callback)
		{
			m_Callbacks.push_back(callback);

			return make_token(new Token(*this, callback));
		}

		/**
		 * Invokes all the callbacks in the list with the given arguments.
		 */
		template<typename... Args>
		void invoke(Args... args)
		{
			for(auto& callback : m_Callbacks) {
				callback(args...);
			}
		}

	private:
		/**
		 * Removes a callback from the list.
		 *
		 * \param callback: The callback to remove
		 */
		void remove(const std::remove_reference_t<CallbackType> & callback)
		{
			m_Callbacks.remove(callback);
		}

		List<CallbackType> m_Callbacks;
	};
}

#define TOKEN(x) decltype(x)::Token
