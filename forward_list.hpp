#pragma once

#include "forward_iterator.hpp"

namespace jl
{
	template <class ElemType>
	class forward_list
	{
		using node = forward_node<ElemType>;
		using iterator = forward_iterator<ElemType, node>;

		node* first = nullptr;

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
		}
		void pop_front()
		{
			if (first)
			{
				node* temp = first->next;
				delete first;
				first = temp;
			}
		}
		iterator begin() const { return iterator(first); }
		iterator end() const { return iterator(nullptr); }
		static int getNodeInst() { return node::node_inst; }
	};
}