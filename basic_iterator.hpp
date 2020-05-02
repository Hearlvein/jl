#pragma once

namespace jl
{
	template<class ContainerNode, class NodeVal>
	class basic_iterator
	{
		ContainerNode* crt = nullptr;

	public:
		basic_iterator(ContainerNode* lhs) : crt(lhs) {}
		const basic_iterator& operator++()
		{
			crt = crt->next;
			return *this;
		}
		bool operator!=(const basic_iterator& lhs) { return crt != lhs.crt; }
		const NodeVal* operator*() const { return crt->val; }
		const NodeVal* operator->() const { return crt->val; }
	};
}