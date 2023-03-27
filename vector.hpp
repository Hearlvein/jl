#pragma once

#include <iostream>
#include <cassert>
#include <vector>

namespace jl
{
	/*
	General-purpose array with dynamic size
	Capacity can only be reduced with clear
	*/
	template<typename T>
	class vector
	{
	public:
		vector() :
			m_size(0), m_capacity(0), m_data(nullptr)
		{ }
		~vector()
		{
			clear();
		}

		// Size modifiers
		void reserve(std::size_t newCapacity)
		{
			if (newCapacity > m_capacity)
			{
				// std::cerr << "Re-allocating vector!" << std::endl;
				// Allocate new block of memory
				T* newMemoryBlock = (T*)::operator new[](sizeof(T) * newCapacity);
				for (std::size_t i = 0; i < m_size; ++i)
				{
					::new(newMemoryBlock + i) T(std::move(m_data[i]));	// calling move ctor
					m_data[i].~T();
				}

				// Delete old block of memory
				::operator delete[](m_data, sizeof(T) * m_capacity);

				// Update state
				m_data = newMemoryBlock;
				m_capacity = newCapacity;
			}
		}
		void resize(std::size_t size)
		{
			if (size > m_capacity)			// Need to extend vector capacity
				reserve(capacityForSize(size));	// May perform a heap re-allocation
			
			else if (size < m_size)
			{
				std::size_t nbElementsToDelete = m_size - size;
				for (std::size_t i = 0; i < nbElementsToDelete; ++i)
					pop_back();
			}

			m_size = size;
		}
		void clear()
		{
			// Deletes wihout freeing and sets size to 0
			resize(0);

			// Free all dynamically-allocated memory
			::operator delete[](m_data, sizeof(T) * m_capacity);
			m_capacity = 0;
		}
		void shrink_to_fit()
		{
			if (std::size_t offset = m_capacity - m_size; offset > 0)
			{
				::operator delete[](&back(), offset * sizeof(T));
				m_capacity = m_size;
			}
		}

		// Size accessors
		std::size_t capacity()	const { return m_capacity; }
		std::size_t size()		const { return m_size; }
		bool empty()			const { return m_size == 0; }

		// Modifiers
		template<typename... Args>
		void emplace_back(Args&&... args)
		{
			std::cout << "emplace back" << std::endl;
			resize(m_size + 1);		// May perform a heap allocation
			::new(&back()) T(std::forward<Args>(args)...);
			//::new(&back()) T(args...);
		}
		void push_back(const T&& item)
		{
			std::cout << "push back move" << std::endl;
			emplace_back(std::move(item));
		}
		void push_back(const T& item)
		{
			std::cout << "push back const ref" << std::endl;
			emplace_back(item);
		}
		void pop_back()
		{
			assert(!empty());

			// Capacity is not reduced
			m_data[--m_size].~T();
		}

		// Accessors
		T& operator[](std::size_t index)
		{
			assert(index < m_size);

			return m_data[index];
		}
		T& back()
		{
			return operator[](m_size - 1);
		}

		// Iterators
		class iterator
		{
		public:
			iterator(T* ptr = nullptr) : m_ptr(ptr) {}
			~iterator() {}

			iterator& operator++()
			{
				++m_ptr;
				return *this;
			}

			T& operator*() { return *m_ptr; }
			T* operator->() { return m_ptr; }
			
			bool operator==(const iterator& other) const { return m_ptr == other.m_ptr; }
			bool operator!=(const iterator& other) const { return !(*this == other); }

		private:
			T* m_ptr;
		};

		iterator begin() const
		{
			return iterator(m_data);
		}

		iterator end()
		{
			return iterator(m_data + m_size);
		}

	private:
		std::size_t capacityForSize(std::size_t size) const
		{
			// @return: Always >= size. size=0 => capacity=0
			std::size_t ret = (std::size_t)(1.5 * size);
			return ret;
		}

	private:
		std::size_t m_capacity = 0;
		std::size_t m_size = 0;
		T* m_data = nullptr;
	};
}