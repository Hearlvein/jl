#include <iostream>

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

public:
	struct forward_iterator
	{
		forward_iterator(node* lhs) : crt(lhs) {}
		const forward_iterator& operator++()
		{
			crt = crt->next;
			return *this;
		}
		bool operator!=(const forward_iterator& lhs) { return crt != lhs.crt; }
		const C& operator*() const { return crt->val; }
		const C* operator->() const { return crt->val; }
		node* crt = nullptr;
	};

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
	forward_iterator begin() const { return forward_iterator(first); }
	forward_iterator end() const { return forward_iterator(nullptr); }
	static int getNodeInst() { return node::node_inst; }
};
template <class C> int forward_list<C>::node::node_inst = 0;

class Obj
{
public:
	Obj(int n) : val(n)
	{
		std::cout << "ctor (void)" << std::endl;
		instances++;
	}
	Obj(const Obj& obj)
	{
		std::cout << "ctor (copy)" << std::endl;
		val = obj.val;
		instances++;
	}
	~Obj()
	{
		std::cout << "dtor" << std::endl;
		instances--;
	}
	int getVal() const { return val; }

	static int instances;

private:
	int val;
};
int Obj::instances = 0;

int main()
{
	{
		forward_list<Obj> myList;
		myList.push_front(Obj(1));
		myList.push_front(Obj(3));
		myList.push_front(Obj(5));

		for (auto it = myList.begin(); it != myList.end(); ++it)
			std::cout << it->getVal() << std::endl;

		myList.pop_front();

		for (auto it = myList.begin(); it != myList.end(); ++it)
			std::cout << it->getVal() << std::endl;
	}

	std::cout << "number of obj: " << Obj::instances << std::endl;
	std::cout << "number of nodes: " << forward_list<Obj>::getNodeInst() << std::endl;

	return 0;
}
