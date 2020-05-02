#pragma once

namespace jl
{
	template <class ElemType>
	class forward_node
	{
	public:
		forward_node() { node_inst++; }
		~forward_node()
		{
			if (val) delete val;
			node_inst--;
		}

		ElemType* val = nullptr;
		forward_node* next = nullptr;

		static int node_inst;
	};

	template <class ElemType> int forward_node<ElemType>::node_inst = 0;
}