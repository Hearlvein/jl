// Custom-made libs
#include "forward_list.hpp"
#include "timer.hpp"

// Stantard libs
#include <forward_list>
#include <iostream>

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
		jl::timer t("Custom list");

		jl::forward_list<Obj> myList;
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
	std::cout << "number of nodes: " << jl::forward_list<Obj>::getNodeInst() << std::endl;

	/*{
		jl::timer t("Stantard list");

		std::forward_list<Obj> myList;
		myList.push_front(Obj(1));
		myList.push_front(Obj(3));
		myList.push_front(Obj(5));

		for (auto it = myList.begin(); it != myList.end(); ++it)
			std::cout << it->getVal() << std::endl;

		myList.pop_front();

		for (auto it = myList.begin(); it != myList.end(); ++it)
			std::cout << it->getVal() << std::endl;
	}*/

	std::cin.get();

	return 0;
}
