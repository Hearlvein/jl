// Custom-made libs
#include "list.hpp"
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

		jl::list<Obj> myList;
		myList.push_back(Obj(1));
		myList.push_back(Obj(3));
		myList.push_back(Obj(5));

		std::cout << " -------- values --------" << std::endl;
		for (jl::list<Obj>::iterator it = myList.begin(); it != myList.end(); ++it)
		{
			std::cout << it->getVal() << std::endl;
		}
	}

	std::cout << "number of obj: " << Obj::instances << std::endl;
	std::cout << "number of nodes: " << jl::list<Obj>::getNodeInstances() << std::endl;

	std::cin.get();

	return 0;
}
