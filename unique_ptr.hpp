#pragma once

#include <iostream>

#include "swap.hpp"

namespace jl
{
	template <typename T>
	class unique_ptr
	{
	public:
		// Primary constructor
		unique_ptr(T* ptr = nullptr)
		{
			if (ptr != nullptr)
				swap(ptr, m_ptr);
		}

		// Copy constructor
		unique_ptr(T& other)
		{
			m_ptr = other.ptr;
			other.ptr = nullptr;
		}

		// Move constructor
		unique_ptr(T&& other)
		{
			m_ptr = other.ptr;
			other.ptr = nullptr;
		}

		// Destructor
		~unique_ptr()
		{
			if (m_ptr != nullptr)
				delete m_ptr;
		}

		// Assignement operator
		unique_ptr& operator=(T* ptr)
		{
			if (m_ptr != nullptr)
				delete m_ptr;

			swap(ptr, m_ptr);
			return *this;
		}

		T& operator*()
		{
			return *m_ptr;
		}

		T* operator->()
		{
			return m_ptr;
		}

	private:
		T* m_ptr = nullptr;
	};
}