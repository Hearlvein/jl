#pragma once

#include "forward_iterator.hpp"
#include <iostream>

namespace jl
{
	template <class ElemType>
	class forward_list
	{
		using node = forward_node<ElemType>;
		using iterator = forward_iterator<ElemType, node>;

		node* first = nullptr;
		int size = 0;

	public:
		forward_list() {}
		~forward_list()
		{
			while (first) pop_front();
		}
		void push_front(const ElemType& obj)
		{
			if (!first)
			{
				first = new node;
				first->val = new ElemType(obj);
				first->next = nullptr;
			}
			else
			{
				node* temp = first;
				first = new node;
				first->val = new ElemType(obj);
				first->next = temp;
			}
			std::cout << "creating node pointer at: " << first << std::endl;
			++size;
		}
		void pop_front()
		{
			if (first)
			{
				node* temp = first->next;
				delete first;
				first = temp;
			}
			--size;
		}
		void debug()
		{
			std::cout << "----------------------- START DEBUGGING----------------------------" << std::endl;

			std::cout << "list size: " << size << std::endl;
			auto it = begin();
			for (int i = 0; i < size; ++i)
			{
				std::cout << "iterator #" << i << ":" << std::endl;
				std::cout << "\t- node ref address: " << it.getNode() << std::endl;
				
				if (i+1 < size) ++it;
			}

			std::cout << "----------------------- END DEBUGGING------------------------------" << std::endl;
		}
		const iterator begin() const { return iterator(first); }
		const iterator end() const { return iterator(nullptr); }
		const iterator erase(iterator _first, const iterator& _last)
		{
			iterator to_return(_first);
			if (_first == _last)	// Single removal
			{
				if (_first == first)	// First element
				{
					to_return = first->next;
					pop_front();
				}
				else					// Random element
				{
					iterator prev(first);
					while ((prev + 1) != _first)
						++prev;

					debug();

					prev.getNode()->next = _first.getNode()->next;
					delete _first.getNode();
				}
			}

			return to_return;
		}
		static int getNodeInst() { return node::node_inst; }
	};
}