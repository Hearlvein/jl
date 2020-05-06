#pragma once

#include <iostream>

namespace jl
{
	template <class ElemType>
	class list
	{
		struct ListNode
		{
			ListNode(const ElemType& element) : data(element) { s_instances++; }
			~ListNode() { s_instances--; }

			ListNode* prev = nullptr;
			ListNode* next = nullptr;
			ElemType data;

			static int s_instances;
		};

		ListNode* first_node;
		ListNode* last_node;	// existing node
		
	public:
		class iterator
		{
		public:
			iterator(const iterator& copy) { node_pointer = copy.node_pointer; }
			~iterator() {}

			iterator& operator=(const iterator& lhs)
			{
				node_pointer = lhs.node_pointer;
			}

			ElemType& operator*()
			{
				return node_pointer->data;
			}

			ElemType* operator->()
			{
				return &(node_pointer->data);
			}

			iterator& operator++()
			{
				node_pointer = node_pointer->next;
				return *this;
			}

			bool operator==(const iterator& lhs) const
			{
				return node_pointer == lhs.node_pointer;
			}

			bool operator!=(const iterator& lhs) const
			{
				return !(*this == lhs);
			}

		private:
			friend jl::list<ElemType>;	// to use the private constructor with a node pointer
			iterator(ListNode* _node_ptr) : node_pointer(_node_ptr) {}

			ListNode* node_pointer = nullptr;
		};

		list() {}
		~list()
		{
			while (!empty())
				pop_back();
		}

		bool empty() const
		{
			return first_node == nullptr;
		}

		void push_back(const ElemType& element)
		{
			ListNode* heap_node = new ListNode(element);

			if (empty())	// adding the first element
			{
				first_node = last_node = heap_node;	// last and first point towards the same data
			}
			else
			{
				heap_node->prev = last_node;	// link to previous
				last_node->next = heap_node;	// link to next
				last_node = heap_node;			// modify ending
			}
		}

		void pop_back()
		{
			if (first_node == last_node)	// only one element in the list
			{
				delete first_node;
				first_node = last_node = nullptr;	// resetting pointers
			}
			else
			{
				last_node = last_node->prev;
				delete last_node->next;
				last_node->next = nullptr;
			}
		}

		iterator begin() const
		{
			return iterator(first_node);
		}

		iterator end() const
		{
			return iterator(nullptr);
		}

		static int getNodeInstances() { return ListNode::s_instances; }
	};

	template <class ElemType> int list<ElemType>::ListNode::s_instances = 0;
}