#pragma once

#include "basic_iterator.hpp"

namespace jl
{
	template <class C>
	class forward_list
	{
		struct node
		{
			node() { node_inst++; }
			~node()
			{
				if (val) delete val;
				node_inst--;
			}
			C* val = nullptr;
			node* next = nullptr;
			static int node_inst;
		};
		node* first = nullptr;

		using iterator = basic_iterator<node, C>;

	public:
		

		forward_list() {}
		~forward_list()
		{
			while (first) pop_front();
		}
		void push_front(const C& obj)
		{
			if (!first)
			{
				first = new node;
				first->val = new C(obj);
				first->next = nullptr;
			}
			else
			{
				node* temp = first;
				first = new node;
				first->val = new C(obj);
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
	template <class C> int forward_list<C>::node::node_inst = 0;
}