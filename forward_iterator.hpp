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
		const forward_iterator& operator++()
		{
			crt = crt->next;
			return *this;
		}
		bool operator==(const forward_iterator& lhs) const { return crt == lhs.crt; }
		bool operator!=(const forward_iterator& lhs) const { return !(crt == lhs.crt); }
		const ElemType* operator*() const { return crt->val; }
		const ElemType* operator->() const { return crt->val; }
	};
}