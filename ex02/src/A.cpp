
#include "../includes/A.hpp"

A::A(void)
{
	std::cout << "[A] Default constructor called. " <<
				std::endl;
	return;
}

A::A(const A& other)
{
	std::cout << "[A] Copy constructor called. " <<
				std::endl;
	*this = other;
	return;
}

A& A::operator=(const A& other)
{
	std::cout << "[A] Copy assignment operator called. " <<
		std::endl;

	if(this != &other)
		return *this;
	return *this;
}

	// Destructor
A::~A(void)
{
	return;
}
