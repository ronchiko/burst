#pragma once

#include "../Types.h"

namespace burst {

	template<typename T, u32 Capacity>
	class CappedStack
	{
	public:
		INLINE_XCEPTION(StackEmpty, "Stack is empty");
		INLINE_XCEPTION(StackFull, "Stack is full");

		/**
		 * Creates a new capped stack.
		 */
		constexpr CappedStack();

		/**
		 * Pushes a new item into the capped stack.
		 *
		 * \param value: The item to push to the stack
		 * \throw CappedStack::StackFull exception when the stack is full
		 */
		void push(T value);

		/**
		 * Pops the top element from the stack.
		 *
		 * \throw CappedStack::StackEmpty when the stack is empty
		 * \returns: The popped element
		 */
		T pop();

		/**
		 * Returns true if the stack is empty.
		 */
		constexpr bool empty() const;

		/**
		 * Returns true if the stack is full.
		 */
		constexpr bool full() const;

		/**
		 * Returns the amount of items in the stack.
		 */
		constexpr u32 size() const;

		/**
		 * Gets an item from the stack at an index.
		 *
		 * \param index: The index of the item
		 */
		const T& operator[](u32 index) const;

		/**
		 * Gets an item from the stack at an index.
		 *
		 * \param index: The index of the item
		 */
		T& at(u32 index);

	private:
		u32 m_Used;
		T m_Stack[Capacity];
	};
}

template<typename T, burst::u32 Capacity>
constexpr burst::CappedStack<T, Capacity>::CappedStack()
	: m_Used(0)
	, m_Stack{}
{}

template<typename T, burst::u32 Capacity>
void burst::CappedStack<T, Capacity>::push(T value)
{
	if(m_Used >= Capacity) {
		throw StackFull();
	}

	m_Stack[m_Used++] = ::std::move(value);
}

template<typename T, burst::u32 Capacity>
T burst::CappedStack<T, Capacity>::pop()
{
	if(m_Used <= 0) {
		throw StackEmpty();
	}

	return ::std::move(m_Stack[--m_Used]);
}

template<typename T, burst::u32 Capacity>
constexpr bool burst::CappedStack<T, Capacity>::empty() const
{
	return m_Used <= 0;
}

template<typename T, burst::u32 Capacity>
constexpr bool burst::CappedStack<T, Capacity>::full() const
{
	return m_Used >= Capacity;
}

template<typename T, burst::u32 Capacity>
constexpr burst::u32 burst::CappedStack<T, Capacity>::size() const
{
	return m_Used;
}

template<typename T, burst::u32 Capacity>
const T& burst::CappedStack<T, Capacity>::operator[](u32 index) const
{
	return CONST_PROXY(this)->at(index);
}

template<typename T, burst::u32 Capacity>
T& burst::CappedStack<T, Capacity>::at(u32 index)
{
	if(index < 0 || index >= m_Used) {
		throw std::out_of_range();
	}

	return m_Stack[index];
}