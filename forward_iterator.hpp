#pragma once

#include "forward_node.hpp"

namespace jl
{
	template<class ElemType, class node>
	class forward_iterator
	{
		node* crt = nullptr;

	public:
		forward_iterator(node* lhs) : crt(lhs) {}
		forward_iterator& operator=(const forward_iterator& lhs)
		{
			crt = lhs.crt;
			return *this;
		}
		forward_iterator& operator++()
		{
			crt = crt->next;
			return *this;
		}
		friend forward_iterator operator+(const forward_iterator& lhs, int off)
		{
			auto to_return = lhs;
			to_return += off;
			return to_return;
		}
		forward_iterator& operator+=(int off)
		{
			for (int i = 0; i < off; ++i)
				operator++();
			return *this;
		}
		bool operator==(const forward_iterator& lhs) const { return crt == lhs.crt; }
		bool operator!=(const forward_iterator& lhs) const { return !(crt == lhs.crt); }
		ElemType* operator*() const { return crt->val; }
		ElemType* operator->() const { return crt->val; }
		node* getNode() { return crt; }
	};
}