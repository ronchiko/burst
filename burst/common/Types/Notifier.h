#pragma once

#include "../Types.h"

#include "traits/generic.h"
#include "traits/function.h"
#include "traits/member_function.h"

namespace burst {
	/**
	 * RAII object for containing a subcription for a notifier.
	 */
	struct Subscription
	{
	public:
		explicit Subscription()
			: m_RemoveMethod(nullptr)
		{}

		explicit Subscription(std::function<void()> remove_function)
			: m_RemoveMethod(remove_function)
		{}

		NOT_COPIABLE(Subscription);

		Subscription(Subscription&& subscription) noexcept
			: m_RemoveMethod(subscription.m_RemoveMethod)
		{}

		Subscription& operator=(Subscription&& subscription) noexcept
		{
			_release();

			m_RemoveMethod = subscription.m_RemoveMethod;
			subscription.m_RemoveMethod = nullptr;

			return *this;
		}

		~Subscription()
		{
			try {
				_release();
			} catch(...) {} // Mute exceptions
		}

	private:
		/**
		 * Invokes the release method and resets it.
		 */
		void _release()
		{
			if(nullptr != m_RemoveMethod) {
				m_RemoveMethod();
				m_RemoveMethod = nullptr;
			}
		}

		std::function<void()> m_RemoveMethod;
	};

	/**
	 * A list object to notify
	 */
	template<typename Subscriber>
	class NotificationList
	{
	public:
		/**
		 * Adds a new subscriber to this notifcation list, returns a subscription
		 * to this storage.
		 *
		 * \param subscriber: The subscriber to add
		 * \return: A subscription object, while this object exists the function will be registered.
		 */
		Subscription subscribe(Subscriber *subscriber)
		{
			register_observer(subscriber);

			return Subscription{ [subscriber, this]() {
				this->unregister_observer(subscriber);
			} };
		}

	private:
		/**
		 * Adds an new observer to this notification list.
		 *
		 * \param observer: The observer to add
		 */
		void register_observer(Subscriber *observer)
		{
			m_Subcribers.insert(observer);
		}

		/**
		 * Removes an observer from this notification list .
		 *
		 * \param observer: The observer to remove
		 */
		void unregister_observer(Subscriber *observer)
		{
			m_Subcribers.erase(observer);
		}

	protected:
		Set<Subscriber *> m_Subcribers;
	};

	template<typename T>
	class Notifier;

	template<burst::function CallbackType>
	class Notifier<CallbackType> : public NotificationList<CallbackType>
	{
	public:
		/**
		 * Invokes a function to the entire notification list.
		 *
		 * \param args...: The argument to pass
		 */
		template<typename... Args>
		void notify(Args&...args)
		{
			static_assert(burst::function_traits<CallbackType>::argument_count ==
							  sizeof...(args),
						  "Argument count of function doesnt match");

			for(const auto& observer :
				NotificationList<CallbackType>::m_Subcribers) {
				observer(args...);
			}
		}
	};

	// Notifier for interface types
	template<burst::abstract ObserverType>
	class Notifier<ObserverType> : public NotificationList<ObserverType>
	{
	public:
		/**
		 * Invokes a function to the entire notification list.
		 * 
		 * \param function: The function that to invoke
		 * \param args...: The argument to pass
		 */
		template<burst::member_function Func, typename... Args>
		void notify(Func function, Args&...args)
		{
			static_assert(burst::member_function_traits<Func>::argument_count ==
							  sizeof...(args),
						  "Argument count of function doesnt match");

			for(const auto& observer :
				NotificationList<ObserverType>::m_Subcribers) {
				(observer->*function)(args...);
			}
		}
	};
}
