// Custom-made libs
#include "list.hpp"
#include "timer.hpp"
#include "unique_ptr.hpp"
#include "vector.hpp"

// Stantard libs
#include <forward_list>
#include <iostream>

class Obj
{
public:
	Obj(int n = 0) : val(n)
	{
		std::cout << "obj ctor (" << n << ")" << std::endl;
		instances++;
	}
	Obj(const Obj& other) : val(other.val)
	{
		std::cout << "obj ctor (copy)" << std::endl;
		instances++;
	}
	Obj(const Obj&& other) : val(std::move(other.val))
	{
		std::cout << "obj ctor (move)" << std::endl;
		instances++;
	}
	~Obj()
	{
		std::cout << "obj dtor" << std::endl;
		instances--;
	}
	Obj& operator=(const Obj& other)
	{
		std::cout << "Obj assignement" << std::endl;
		val = other.val;
		return *this;
	}
	int getVal() const { return val; }

	static int instances;

private:
	int val;
};
int Obj::instances = 0;

int main()
{
	// jl::list
	/*{
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
	}*/

	// jl::unique_ptr
	/*{
		jl::timer t("Unique ptr");
		std::cout << " -----------------------------------------------" << std::endl;

		jl::unique_ptr<Obj> ptr1 = new Obj(5);
		std::cout << ptr1->getVal() << std::endl;
		ptr1 = new Obj(6);
		std::cout << ptr1->getVal() << std::endl;

		Obj lvalue(78);
		Obj* ptrtolvalue = &lvalue;
		jl::unique_ptr<Obj> ptr2;
		ptr2 = ptrtolvalue;
	}*/

	// jl::vector
	{
		/*{
			jl::vector<int> vi;
			vi.push_back(1);
			vi.push_back(2);
			vi.push_back(3);
			vi.push_back(4);
			vi.push_back(5);

			for (std::size_t i = 0; i < vi.size(); ++i)
				std::cout << vi[i] << " ";
		}*/

		std::cout << "\n\n\n\n\ncreating vector<Obj>" << std::endl;
		std::cout << "remaining obj in memory: " << Obj::instances << std::endl;
		{
			jl::vector<Obj> vo;
			for (std::size_t i = 0; i < 5; ++i)
			{
				std::cout << "------------- i = " << i << " -----------------" << std::endl;
				vo.push_back(Obj(i));
			}

			std::cout << "------------------ print ------------------------ " << std::endl;
			for (std::size_t i = 0; i < vo.size(); ++i)
				std::cout << vo[i].getVal() << " ";

			std::cout << std::endl;

			std::cout << "------------------ vector status ------------------------ " << std::endl;
			std::cout << "Size = " << vo.size() << std::endl;
			std::cout << "Capacity = " << vo.capacity() << std::endl;
			std::cout << std::endl;

			std::cout << "------------------ Shrinking to fit ------------------------ " << std::endl;
			vo.shrink_to_fit();

			std::cout << "------------------ vector status ------------------------ " << std::endl;
			std::cout << "Size = " << vo.size() << std::endl;
			std::cout << "Capacity = " << vo.capacity() << std::endl;
			std::cout << std::endl;

			for (jl::vector<Obj>::iterator it = vo.begin(); it != vo.end(); ++it)
				std::cout << it->getVal() << " ";
			std::cout << "\n---------- before desotrying vector--------- " << std::endl;
		}
		std::cout << "remaining obj in memory: " << Obj::instances << std::endl;
	}
	//std::cin.get();

	return 0;
}
