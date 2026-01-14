#include "../includes/A.hpp"
#include "../includes/B.hpp"
#include "../includes/C.hpp"
#include <cstdlib>
#include <ctime>

Base* generate(void)
{
	int	rand = std::rand() % 3;

	if (rand == 0)
		return (new A);
	else if (rand == 1)
		return (new B);
	else if (rand == 2)
		return (new C);
	else
		return (NULL);
}

void identify(Base* p)
{
	if (dynamic_cast<A*>(p))
		std::cout << "Actual type of the object pointed to by pointer: A\n";
	else if (dynamic_cast<B*>(p))
		std::cout << "Actual type of the object pointed to by pointer: B\n";
	else if (dynamic_cast<C*>(p))
		std::cout << "Actual type of the object pointed to by pointer: C\n";
}

void identify(Base& p)
{
	Base ptr;

	try
	{
		ptr = dynamic_cast<A&>(p);
		std::cout << "Actual type of the object pointed to by reference: A\n";
	}
	catch(std::exception &e) {}
	try
	{
		ptr = dynamic_cast<B&>(p);
		std::cout << "Actual type of the object pointed to by reference: B\n";
	}
	catch(std::exception &e) {}
	try
	{
		ptr = dynamic_cast<C&>(p);
		std::cout << "Actual type of the object pointed to by reference: C\n";
	}
	catch(std::exception &e) {}
}

int main()
{
	srand(time(NULL));
	Base *array[10];
	for (size_t i = 0; i < 10; i++)
	{
		array[i] = generate();
		identify(array[i]);
		identify(*array[i]);
		std::cout << "\n";
		delete (array[i]);
	}
}
